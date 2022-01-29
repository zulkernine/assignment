import React, { Component } from 'react';
import { TextField, Box, Button, Grid } from "@mui/material";

class MessageTextField extends Component {
    state = {  } 
    render() { 
        return (
          <Grid container>
            <Grid item xs={9}>
              <TextField fullWidth autoFocus />
            </Grid>
            <Grid xs>
              <Button
                variant="contained"
                size="large"
                style={{ marginLeft: "5px" }}
              >
                Send
              </Button>
            </Grid>
          </Grid>
        );
    }
}
 
export default MessageTextField;
