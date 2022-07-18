import React, { Component } from "react";
import Form from "react-validation/build/form";
import Input from "react-validation/build/input";
import CheckButton from "react-validation/build/button";
import { isEmail } from "validator";

import AuthService from "../services/auth.service";

const required = (value) => {
  if (!value) {
    return (
      <div className="alert alert-danger" role="alert">
        This field is required!
      </div>
    );
  }
};

const email = (value) => {
  if (!isEmail(value)) {
    return (
      <div className="alert alert-danger" role="alert">
        This is not a valid email.
      </div>
    );
  }
};

const vusername = (value) => {
  if (value.length < 3 || value.length > 20) {
    return (
      <div className="alert alert-danger" role="alert">
        The username must be between 3 and 20 characters.
      </div>
    );
  }
};

const vpassword = (value) => {
  if (value.length < 6 || value.length > 40) {
    return (
      <div className="alert alert-danger" role="alert">
        The password must be between 6 and 40 characters.
      </div>
    );
  }
};

export default class Register extends Component {
  constructor(props) {
    super(props);
    this.handleRegister = this.handleRegister.bind(this);
    this.onChangeUsername = this.onChangeUsername.bind(this);
    this.onChangeEmail = this.onChangeEmail.bind(this);
    this.onChangePassword = this.onChangePassword.bind(this);

    this.state = {
      username: "",
      email: "",
      password: "",
      successful: false,
      gender: "Men",
      message: "",
    };
  }

  onChangeUsername(e) {
    this.setState({
      username: e.target.value,
    });
  }

  onChangeEmail(e) {
    this.setState({
      email: e.target.value,
    });
  }

  onChangeGender = (e) => {
    this.setState({
      gender: e.target.value,
    });
  };

  onChangePassword(e) {
    this.setState({
      password: e.target.value,
    });
  }

  handleRegister(e) {
    e.preventDefault();

    this.setState({
      message: "",
      successful: false,
    });

    this.form.validateAll();

    if (this.checkBtn.context._errors.length === 0) {
      AuthService.register(
        this.state.username,
        this.state.email,
        this.state.password,
        this.state.gender
      ).then(
        (response) => {
          this.setState({
            message: response.data.message,
            successful: true,
          });
        },
        (error) => {
          const resMessage =
            (error.response &&
              error.response.data &&
              error.response.data.message) ||
            error.message ||
            error.toString();

          this.setState({
            successful: false,
            message: resMessage,
          });
        }
      );
    }
  }

  render() {
    return (
      <div>
        <section className="py-20 bg-light overflow-hidden">
          <div className="position-relative container">
            <div className="position-relative mw-4xl mx-auto">
              <div
                className="position-absolute top-50 start-0 end-0 translate-middle-y bg-info-light ms-n6 me-n6"
                style={{ height: "90%" }}
              ></div>
              <div className="position-relative py-16 pt-md-32 pb-md-20 px-4 px-sm-8 bg-white">
                <div className="mw-lg mx-auto text-center">
                  <h2 className="mb-8">
                    Signing up with social is super quick
                  </h2>
                  <Form
                    onSubmit={this.handleRegister}
                    ref={(c) => {
                      this.form = c;
                    }}
                  >
                    {!this.state.successful && (
                      <div>
                        <div className="form-group">
                          <Input
                            type="text"
                            className="form-control form-control-lg mb-4"
                            placeholder="john007"
                            name="username"
                            value={this.state.username}
                            onChange={this.onChangeUsername}
                            validations={[required, vusername]}
                          />
                        </div>

                        <div className="form-group">
                          <Input
                            type="text"
                            className="form-control form-control-lg mb-4"
                            name="email"
                            placeholder="john@example.com"
                            value={this.state.email}
                            onChange={this.onChangeEmail}
                            validations={[required, email]}
                          />
                        </div>

                        <div className="form-group">
                          <select
                            name="gender"
                            id="gender"
                            className="form-control form-control-lg mb-10"
                            value={this.state.gender}
                            onChange={this.onChangeGender}
                          >
                            <option value="Men">Male</option>
                            <option value="Women">Female</option>
                            <option value={null}>Custom</option>
                          </select>
                        </div>

                        <div className="form-group">
                          <Input
                            type="password"
                            className="form-control form-control-lg mb-10"
                            name="password"
                            placeholder="Password"
                            value={this.state.password}
                            onChange={this.onChangePassword}
                            validations={[required, vpassword]}
                          />
                        </div>

                        <div className="form-group">
                          <button className="mt-12 mt-md-16 btn btn-dark">
                            Sign Up
                          </button>
                        </div>
                      </div>
                    )}

                    {this.state.message && (
                      <div className="form-group">
                        <div
                          className={
                            this.state.successful
                              ? "alert alert-success"
                              : "alert alert-danger"
                          }
                          role="alert"
                        >
                          {this.state.message}
                        </div>
                      </div>
                    )}
                    <CheckButton
                      style={{ display: "none" }}
                      ref={(c) => {
                        this.checkBtn = c;
                      }}
                    />
                  </Form>
                </div>
              </div>
            </div>
          </div>
        </section>
      </div>
    );
  }
}
