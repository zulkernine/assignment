import { Grid, Box } from "@mui/material";
import React, { Component } from "react";

class MessageList extends Component {
  state = {};
  messagesEnd = null;

  scrollToBottom = () => {
    this.messagesEnd.scrollIntoView({ behavior: "smooth" });
  };

  componentDidMount() {
    this.scrollToBottom();
  }

  componentDidUpdate() {
    this.scrollToBottom();
  }

  render() {
    const { messages } = this.props;

    return (
      <div
        style={{
          maxHeight: "90vh",
          overflow: "auto",
        }}
      >
        {/* {
            sentByMyself: false,
            text: "d fsgdshi bgfds gds",
            image: "https://picsum.photos/237/400/400",
          }, */}

        <Grid container direction={"row"}>
          {messages.map((e) => (
            <Grid
              item
              container
              xs={12}
              justifyContent={e.sentByMyself ? "flex-end" : "flex-start"}
              direction={"row"}
            >
              <Grid item>
                <Box
                  margin={1}
                  padding={2}
                  borderRadius={2}
                  bgcolor={e.sentByMyself ? "#0ee6b0" : "#4fb885"}
                >
                  <div>{e.text}</div>
                  <div>
                    <img
                      src={e.image}
                      style={{
                        maxWidth: window.innerWidth * 0.7,
                        objectFit: "contain",
                      }}
                    />
                  </div>
                </Box>
              </Grid>
            </Grid>
          ))}
          <Grid item style={{height:"200px"}}></Grid>
        </Grid>

        <div
          style={{ float: "left", clear: "both", }}
          ref={(el) => {
            this.messagesEnd = el;
          }}
        ></div>
      </div>
    );
  }
}

export default MessageList;
