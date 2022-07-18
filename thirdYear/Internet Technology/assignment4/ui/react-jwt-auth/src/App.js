import React, { Component } from "react";
import { Switch, Route, Link } from "react-router-dom";
// import "bootstrap/dist/css/bootstrap.min.css";

import AuthService from "./services/auth.service";

import Login from "./pages/login.component";
import Register from "./pages/register.component";
import Home from "./pages/home.component";
import Profile from "./pages/profile.component";
import BoardUser from "./pages/board-user.component";
import BoardModerator from "./pages/board-moderator.component";
import BoardAdmin from "./pages/board-admin.component";

// import AuthVerify from "./common/auth-verify";
import EventBus from "./common/EventBus";
import ProductPage from "./pages/product_page";
import CartIconComponent from "./pages/components/cart_icon_nav";
import { ToastContainer } from "react-toastify";
import MyCart from "./pages/mycart";
import authHeader from "./services/auth-header";

class App extends Component {
  constructor(props) {
    super(props);
    this.logOut = this.logOut.bind(this);

    this.state = {
      showModeratorBoard: false,
      showAdminBoard: false,
      currentUser: undefined,
    };
  }

  componentDidMount() {
    const user = AuthService.getCurrentUser();

    if (user) {
      this.setState({
        currentUser: user,
        showModeratorBoard: user.roles.includes("ROLE_MODERATOR"),
        showAdminBoard: user.roles.includes("ROLE_ADMIN"),
      });
    }

    EventBus.on("logout", () => {
      this.logOut();
    });
  }

  componentWillUnmount() {
    EventBus.remove("logout");
  }

  logOut() {
    AuthService.logout();
    this.setState({
      showModeratorBoard: false,
      showAdminBoard: false,
      currentUser: undefined,
    });
  }

  render() {
    const { currentUser, showModeratorBoard, showAdminBoard } = this.state;

    return (
      <div className="">
        <section className="position-relative">
          <nav className="navbar py-0 navbar-expand-lg navbar-light bg-white border-bottom">
            <div className="container-fluid">
              <a className="d-none d-lg-block me-16" href="#"></a>
              {/* <Link
                to={"/"}
                className="navbar-brand fw-bold flex-shrink-0 py-10"
                href="#"
              >
                <img
                  className="img-fluid"
                  src="yofte-assets/logos/yofte-logo.svg"
                  alt=""
                  width="auto"
                />
              </Link> */}
              <Link to={"/home"} className="nav-link">
                <h1>Home</h1>
              </Link>
              {showAdminBoard && (
                <li className="nav-item">
                  <Link to={"/admin"} className="nav-link">
                    Admin Board
                  </Link>
                </li>
              )}

              <div className="d-none d-xl-flex navbar-collapse flex-row-reverse">
                <a
                  className="link-dark ms-auto ms-xl-0 me-10 text-decoration-none"
                  href="#"
                ></a>

                <div
                  className="link-dark align-self-stretch py-10 px-10 border-start text-decoration-none d-flex align-items-center fw-bold"
                  href="#"
                >
                  {currentUser ? (
                    <div className="navbar-nav ml-auto">
                      <li className="nav-item">
                        <Link to={"/profile"} className="nav-link">
                          <svg
                            className="me-3"
                            width="32"
                            height="31"
                            viewBox="0 0 32 31"
                            fill="none"
                            xmlns="http://www.w3.org/2000/svg"
                          >
                            <path
                              d="M16.0006 16.3154C19.1303 16.3154 21.6673 13.799 21.6673 10.6948C21.6673 7.59064 19.1303 5.07422 16.0006 5.07422C12.871 5.07422 10.334 7.59064 10.334 10.6948C10.334 13.799 12.871 16.3154 16.0006 16.3154Z"
                              stroke="currentColor"
                              strokeWidth="1.5"
                              strokeLinecap="round"
                              strokeLinejoin="round"
                            ></path>
                            <path
                              d="M24.4225 23.8963C23.6678 22.3507 22.4756 21.0445 20.9845 20.1298C19.4934 19.2151 17.7647 18.7295 15.9998 18.7295C14.2349 18.7295 12.5063 19.2151 11.0152 20.1298C9.52406 21.0445 8.33179 22.3507 7.57715 23.8963"
                              stroke="currentColor"
                              strokeWidth="1.5"
                              strokeLinecap="round"
                              strokeLinejoin="round"
                            ></path>
                          </svg>
                          {currentUser.username}
                        </Link>
                      </li>
                      <li className="nav-item">
                        <a
                          href="/login"
                          className="nav-link"
                          onClick={this.logOut}
                        >
                          LogOut
                        </a>
                      </li>
                    </div>
                  ) : (
                    <div className="navbar-nav ml-auto">
                      <li className="nav-item">
                        <Link to={"/login"} className="nav-link">
                          Login
                        </Link>
                      </li>

                      <li className="nav-item">
                        <Link to={"/register"} className="nav-link">
                          Sign Up
                        </Link>
                      </li>
                    </div>
                  )}
                </div>
                {authHeader().Authorization && <CartIconComponent />}
              </div>
            </div>
          </nav>
        </section>
        <div>
          <Switch>
            <Route exact path={["/", "/home"]} component={Home} />
            <Route exact path="/login" component={Login} />
            <Route exact path="/register" component={Register} />
            <Route exact path="/profile" component={Profile} />
            <Route path="/user" component={BoardUser} />
            <Route path="/cart" component={MyCart} />
            <Route path="/mod" component={BoardModerator} />
            <Route path="/admin" component={BoardAdmin} />
            <Route path="/product/:id" component={ProductPage} />
          </Switch>
        </div>

        {/*<AuthVerify logOut={this.logOut}/> */}
      </div>
    );
  }
}

export default App;
