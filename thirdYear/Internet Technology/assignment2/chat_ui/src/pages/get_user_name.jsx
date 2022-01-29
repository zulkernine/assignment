import React, { Component } from "react";
import TextField from "@mui/material/TextField";
import { Box, Button, Container } from "@mui/material";
import socket from "../data/socket";
import EventNames from "../data/event_names";

class GetUserName extends Component {
  state = {
    userName: "",
  };

  render() {
    return (
      <div
        style={{
          color: "#4285F4",
          height: "100vh",
          width: "100wh",
          display: "flex",
          justifyContent: "center",
          alignItems: "center",
        }}
      >
        <Container maxWidth="xs">
          <Box border={2} padding={5} borderRadius={5}>
            <TextField
              required
              label="User name"
              focused
              fullWidth
              onChange={(e) => {
                this.setState({ userName: e.target.value });
              }}
              helperText="User name will help others to identify you"
            />
            <div style={{ height: "20px" }}></div>
            <Button
              variant="contained"
              onClick={() => {
                if (this.state.userName !== "") {
                  console.log("Username: " + this.state.userName);
                  socket.emit(EventNames.registerUser, this.state.userName);
                } else alert("User name should not be empty");
              }}
            >
              Enter
            </Button>
          </Box>
        </Container>
      </div>
    );
  }
}

export default GetUserName;
