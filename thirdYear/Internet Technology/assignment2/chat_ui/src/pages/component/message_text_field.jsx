import React, { Component } from "react";
import {
  TextField,
  FormControlLabel,
  Button,
  Grid,
  FormGroup,
  Typography,
  Checkbox,
} from "@mui/material";
import socket from "../../data/socket";
import EventNames from "../../data/event_names";

class MessageTextField extends Component {
  constructor(props) {
    super(props);
    this.ref = React.createRef();
  }

  state = { text: "", image: null, attachment: null, broadcast: false };

  handleMessage = (e) => {
    const { text, image, broadcast } = this.state;

    if (text != "" || image != null) {
      this.props.handleSent(text, image, broadcast);
      this.setState({
        text: "",
        image: null,
        attachment: null,
        broadcast: false,
      });
    }
  };

  getBase64(file, cb) {
    let reader = new FileReader();
    reader.readAsDataURL(file);
    reader.onload = function () {
      cb(reader.result);
    };
    reader.onerror = function (error) {
      console.log("Error: ", error);
    };
  }

  handleFileSelect = (event) => {
    const files = Array.from(event.target.files);
    const [file] = files;
    this.getBase64(file, (result) => {
      this.setState({ image: result, attachment: file });
      console.log(result);
    });
  };

  handleCheck = (e) => {
    this.setState({ broadcast: e.target.checked });
    console.log(e.target.checked);
  };

  render() {
    const { ref } = this;

    return (
      <Grid
        container
        direction="row"
        justifyContent="center"
        alignItems="center"
        spacing={3}
      >
        <Grid item container xs={12}>
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
          <Grid xs={3}>
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
        <Grid item container xs={12}>
          <Grid item xs={6}>
            <Button variant="contained" component="label">
              Upload File
              <input type="file" hidden onChange={this.handleFileSelect} />
            </Button>
            <Typography>{this.state.attachment?.name}</Typography>
          </Grid>
          <Grid item item xs={6}>
            <FormGroup>
              <FormControlLabel
                control={<Checkbox />}
                label="BROADCAST"
                onChange={this.handleCheck}
              />
            </FormGroup>
          </Grid>
        </Grid>
      </Grid>
    );
  }
}

export default MessageTextField;
