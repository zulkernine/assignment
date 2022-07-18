import React, { Component } from "react";
import clothService from "../services/clothService";
import MyEvent from "../services/my_event";
import userService from "../services/user.service";
import CartItemCard from "./components/cart_item";
import KEY from "../KEY.json";

class MyCart extends Component {
  state = {
    cartItems: [],
    userCartItemIds: [],
  };

  componentDidMount() {
    this.init();
    this.state.shippingCharge = Math.floor(Math.random() * 70 + 30);
  }

  async init() {
    const items = await this.getCartList();
    items.forEach(async (e) => {
      const { data } = await clothService.getClothById(e);
      let carts = [...this.state.cartItems];
      carts.push({
        cloth: data,
        quantity: 1,
      });
      this.setState({ cartItems: carts });
    });
  }

  getCartList = async () => {
    const data = await userService.getCartList();
    this.setState({ userCartItemIds: data });
    return data;
  };

  updateCartQuantity = (id, quantity) => {
    let carts = [...this.state.cartItems];
    const index = carts.findIndex((e) => e.cloth.id == id);
    if (index > -1) {
      carts[index].quantity = quantity;
    }
    this.setState({ cartItems: carts });
  };

  getTotal = () => {
    let total = 0;
    this.state.cartItems.forEach(({ cloth, quantity }) => {
      total +=
        Math.round(cloth.price * ((100 - cloth.discount) * 0.01)) * quantity;
    });

    return total;
  };

  getAveragePrice = () => {
    let total = 0,
      q = 0;
    this.state.cartItems.forEach(({ cloth, quantity }) => {
      total +=
        Math.round(cloth.price * ((100 - cloth.discount) * 0.01)) * quantity;
      q += quantity;
    });

    return total / q;
  };

  handleCheckOut = async () => {
    await userService.checkout(this.getAveragePrice());
    alert("Thanks for visisting our store! 😀");
    this.setState({ cartItems: [] });
    MyEvent.fire(KEY.AddedToCart);
  };

  render() {
    const total = this.getTotal();
    const { shippingCharge } = this.state;

    return (
      <dev>
        <section className="py-20 bg-light overflow-hidden">
          <div className="container">
            <div className="p-8 p-lg-20 bg-white">
              <h2 className="mb-8 mb-md-20">Your cart</h2>

              {this.state.cartItems.length == 0 ? (
                <h3>
                  Please add something to your cart, its empty currently.😅 😅
                  😅
                </h3>
              ) : (
                <div className="row align-items-center">
                  <div className="col-12 col-xl-8 mb-8 mb-xl-0">
                    <div className="d-none d-lg-flex row">
                      <div className="col-12 col-lg-6">
                        <h4
                          className="mb-6 text-secondary"
                          style={{ fontSize: "16px" }}
                        >
                          Description
                        </h4>
                      </div>
                      <div className="col-12 col-lg-2">
                        <h4
                          className="mb-6 text-secondary"
                          style={{ fontSize: "16px" }}
                        >
                          Price
                        </h4>
                      </div>
                      <div className="col-12 col-lg-2 text-center">
                        <h4
                          className="mb-6 text-secondary"
                          style={{ fontSize: "16px" }}
                        >
                          Quantity
                        </h4>
                      </div>
                      <div className="col-12 col-lg-2 text-end">
                        <h4
                          className="mb-6 text-secondary"
                          style={{ fontSize: "16px" }}
                        >
                          Subtotal
                        </h4>
                      </div>
                    </div>
                    <div className="mb-12 py-6 border-top border-bottom">
                      {this.state.cartItems.map((item, i) => (
                        <div
                          key={i}
                          className="row align-items-center mb-6 mb-md-3"
                        >
                          <CartItemCard
                            item={item}
                            updateCart={this.updateCartQuantity}
                          />
                        </div>
                      ))}
                    </div>
                  </div>
                  <div className="col-12 col-xl-4">
                    <div className="p-6 p-md-12 bg-info">
                      <h3 className="mb-6 text-white">Cart totals</h3>
                      <div className="d-flex mb-8 align-items-center justify-content-between pb-5 border-bottom border-info-light">
                        <span className="text-light">Subtotal</span>
                        <span className="lead fw-bold text-white">
                          ₹{total}
                        </span>
                      </div>
                      <h4 className="mb-2 lead fw-bold text-white">Shipping</h4>
                      <div className="d-flex mb-2 justify-content-between align-items-center">
                        <span className="text-light">Next day</span>
                        <span className="lead fw-bold text-white">
                          ₹{shippingCharge}
                        </span>
                      </div>
                      <div className="d-flex mb-10 justify-content-between align-items-center">
                        <span className="text-light">
                          Shipping to your home address
                        </span>
                        <span className="lead fw-bold text-white">-</span>
                      </div>
                      <div className="d-flex mb-10 justify-content-between align-items-center">
                        <span className="lead fw-bold text-white">
                          Order total
                        </span>
                        <span className="lead fw-bold text-white">
                          ₹{total + shippingCharge}
                        </span>
                      </div>
                      <a
                        className="btn btn-primary w-100 text-uppercase"
                        href="#"
                        onClick={this.handleCheckOut}
                      >
                        Go to Checkout
                      </a>
                    </div>
                  </div>
                </div>
              )}
            </div>
          </div>
        </section>
      </dev>
    );
  }
}

export default MyCart;
