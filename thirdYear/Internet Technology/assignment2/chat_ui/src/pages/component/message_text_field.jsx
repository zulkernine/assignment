import React, { Component } from "react";
import { TextField, Box, Button, Grid } from "@mui/material";
import socket from "../../data/socket";
import EventNames from "../../data/event_names";

class MessageTextField extends Component {
  state = { text: "" };

  handleMessage = (e) => {
    if (this.state.text != "") {
      this.props.handleSent(this.state.text);
      this.setState({ text: "" });
    }
  };

  render() {
    return (
      <Grid container>
        <Grid item xs={9}>
          <TextField
            fullWidth
            autoFocus
            value={this.state.text}
            onChange={(e) => {
              this.setState({ text: e.target.value });
            }}
            size="small"
            onKeyPress={(event) => {
              if (event.key === "Enter") {
                this.handleMessage();
              }
            }}
          />
        </Grid>
        <Grid xs>
          <Button
            variant="contained"
            size="medium"
            style={{ marginLeft: "5px" }}
            onClick={this.handleMessage}
          >
            Send
          </Button>
        </Grid>
      </Grid>
    );
  }
}

export default MessageTextField;
