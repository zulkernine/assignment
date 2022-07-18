import React, { Component } from "react";
import Form from "react-validation/build/form";
import Input from "react-validation/build/input";
import CheckButton from "react-validation/build/button";
import AuthService from "../services/auth.service";

const required = value => {
  if (!value) {
    return (
      <div className="alert alert-danger" role="alert">
        This field is required!
      </div>
    );
  }
};

export default class Login extends Component {
  constructor(props) {
    super(props);
    this.handleLogin = this.handleLogin.bind(this);
    this.onChangeUsername = this.onChangeUsername.bind(this);
    this.onChangePassword = this.onChangePassword.bind(this);

    this.state = {
      username: "",
      password: "",
      loading: false,
      message: ""
    };
  }

  onChangeUsername(e) {
    this.setState({
      username: e.target.value
    });
  }

  onChangePassword(e) {
    this.setState({
      password: e.target.value
    });
  }

  handleLogin(e) {
    e.preventDefault();

    this.setState({
      message: "",
      loading: true
    });

    this.form.validateAll();

    if (this.checkBtn.context._errors.length === 0) {
      AuthService.login(this.state.username, this.state.password).then(
        () => {
          this.props.history.push("/profile");
          window.location.reload();
        },
        error => {
          const resMessage =
            (error.response &&
              error.response.data &&
              error.response.data.message) ||
            error.message ||
            error.toString();

          this.setState({
            loading: false,
            message: resMessage
          });
        }
      );
    } else {
      this.setState({
        loading: false
      });
    }
  }

  render() {
    return (
      <div className="">
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
                    Welcome to apparel store
                  </h2>
                  <Form
                    onSubmit={this.handleLogin}
                    ref={(c) => {
                      this.form = c;
                    }}
                  >
                    <div className="form-group">
                      <label htmlFor="username">Username</label>
                      <Input
                        type="text"
                        className="form-control form-control-lg mb-4"
                        name="username"
                        placeholder="Username"
                        value={this.state.username}
                        onChange={this.onChangeUsername}
                        validations={[required]}
                      />
                    </div>

                    <div className="form-group">
                      <Input
                        type="password"
                        className="form-control form-control-lg mb-4"
                        name="password"
                        placeholder="password"
                        value={this.state.password}
                        onChange={this.onChangePassword}
                        validations={[required]}
                      />
                    </div>

                    <div className="form-group">
                      <button
                        className="btn btn-primary btn-block"
                        disabled={this.state.loading}
                      >
                        {this.state.loading && (
                          <span className="spinner-border spinner-border-sm"></span>
                        )}
                        <span>Login</span>
                      </button>
                    </div>

                    {this.state.message && (
                      <div className="form-group">
                        <div className="alert alert-danger" role="alert">
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
