import React, { Component } from "react";
import MyStorage from "../../services/localService";
import MyEvent from "../../services/my_event";
import KEY from "../../KEY.json";
import userService from "../../services/user.service";
import { toast } from "react-toastify";

class CartIconComponent extends Component {
  state = { itemList: [] };

  componentDidMount() {
    this.getCartList();

    MyEvent.on(KEY.AddedToCart, this.handleAddedToCart);
  }
  componentWillUnmount() {
    MyEvent.remove(KEY.AddedToCart, this.handleAddedToCart);
  }

  handleAddedToCart = async () => {
    const data = await this.getCartList();
    if (data.length > 0) alert("1 item added to cart");
  };

  getCartList = async () => {
    const data = await userService.getCartList();
    this.setState({ itemList: data });
    return data;
  };

  render() {
    return (
      <div>
        <a
          className="link-dark me-12 text-decoration-none d-flex align-items-center"
          href="/cart"
        >
          <svg
            className="me-3"
            width="23"
            height="23"
            viewBox="0 0 23 23"
            fill="none"
            xmlns="http://www.w3.org/2000/svg"
          >
            <path
              d="M18.1159 8.72461H2.50427C1.99709 8.72461 1.58594 9.12704 1.58594 9.62346V21.3085C1.58594 21.8049 1.99709 22.2074 2.50427 22.2074H18.1159C18.6231 22.2074 19.0342 21.8049 19.0342 21.3085V9.62346C19.0342 9.12704 18.6231 8.72461 18.1159 8.72461Z"
              stroke="currentColor"
              strokeWidth="1.5"
              strokeLinecap="round"
              strokeLinejoin="round"
            ></path>
            <path
              d="M6.34473 6.34469V4.95676C6.34473 3.85246 6.76252 2.79338 7.5062 2.01252C8.24988 1.23165 9.25852 0.792969 10.3102 0.792969C11.362 0.792969 12.3706 1.23165 13.1143 2.01252C13.858 2.79338 14.2758 3.85246 14.2758 4.95676V6.34469"
              stroke="currentColor"
              strokeWidth="1.5"
              strokeLinecap="round"
              strokeLinejoin="round"
            ></path>
          </svg>
          <span
            className="d-inline-block text-center bg-light rounded-circle fw-bold"
            style={{ width: "24px", height: "24px" }}
          >
            {this.state.itemList.length}
          </span>
        </a>
      </div>
    );
  }
}

export default CartIconComponent;
