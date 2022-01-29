import React, { Component } from "react";
import "./App.css";
import EventNames from "./data/event_names";
import socket from "./data/socket";
import GetUserName from "./pages/get_user_name";
import { ToastContainer, toast } from "react-toastify";
import "react-toastify/dist/ReactToastify.css";
import MessageRootScreen from "./pages/message_page";

class App extends Component {
  state = {
    isRegistered: false,
  };

  componentDidMount() {
    socket.on(EventNames.registrationSuccessful, (isSuccess) => {
      this.setState({ isRegistered: isSuccess });
      if (isSuccess) {
        toast.success("You are now connected!", {
          position: "top-right",
          autoClose: 2000,
          hideProgressBar: false,
          closeOnClick: true,
          pauseOnHover: true,
          draggable: true,
          progress: undefined,
          limit: 1,
        });
      }
    });
  }

  render() {
    return (
      <div>
        <ToastContainer />
        {!this.state.isRegistered ? (
          <MessageRootScreen />
        ) : (
          <GetUserName />
        )}
      </div>
    );
  }
}

export default App;
