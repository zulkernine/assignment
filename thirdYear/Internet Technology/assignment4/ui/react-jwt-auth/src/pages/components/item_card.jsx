import React, { Component } from "react";
import { withRouter } from "react-router-dom";
import { ReactComponent as Star } from "../../yofte-assets/elements/star-gold.svg";
import MyStorage from "../../services/localService";
import MyEvent from "../../services/my_event";
import KEY from "../../KEY.json";
import userService from "../../services/user.service";

class ItemCard extends Component {
  state = {};

  gotoProductPagr = (id) => {
    this.props.history.push("/product/" + id);
  };

  handleAddtoCart = async () => {
    const { cloth } = this.props;
    await this._addToUserCart(cloth.id);
    MyEvent.fire(KEY.AddedToCart);
  };

  _addToUserCart = async (id)=>{
    await userService.addToCart(id);
  }

  render() {
    const { cloth } = this.props;

    return (
      <div
        onClick={() => {
          this.gotoProductPagr(cloth["id"]);
        }}
      >
        <div className="p-6 bg-white">
          {cloth.discount && (
            <span className="badge bg-transparent border border-2 border-danger rounded-pill fw-bold text-danger">
              -{cloth.discount}%
            </span>
          )}
          {cloth.categories.findIndex((e) => e == "New") > -1 && (
            <span className="badge bg-transparent border border-2 border-info rounded-pill fw-bold text-info mx-1">
              NEW
            </span>
          )}
          <a
            className="d-block px-6 mt-6 mb-2 link-dark text-decoration-none"
            href="#"
          >
            <img
              className="mb-5 mx-auto w-100 img-fluid"
              style={{ height: "224px", objectFit: "contain" }}
              src={cloth["images"][0]}
              alt=""
            />
            <h5 className="mb-2">{cloth["name"]}</h5>
            <p className="h6 text-info">
              <span>₹{cloth["price"]}</span>
              {/* <span className="small text-muted fw-normal text-decoration-line-through">
                  $33.69
                </span> */}
            </p>
          </a>
          <div className="ms-auto me-2 d-flex align-items-center justify-content-center">
            <h6 className="pt-1">
              {" "}
              <span className="font-weight-bold">{cloth["rating"]} <Star/>  </span>(
              {cloth["reviews"]} reviews )
            </h6>
          </div>
          <a
            className="ms-auto me-2 d-flex align-items-center justify-content-center border rounded-3"
            href="#"
            onClick={(e)=>{
              e.stopPropagation();
              this.handleAddtoCart();
            }}
            style={{ width: "48px", height: "48px" }}
          >
            <svg
              width="12"
              height="12"
              viewBox="0 0 12 12"
              fill="none"
              xmlns="http://www.w3.org/2000/svg"
            >
              <rect x="5" width="2" height="12" fill="#161616"></rect>
              <rect
                x="12"
                y="5"
                width="2"
                height="12"
                transform="rotate(90 12 5)"
                fill="#161616"
              ></rect>
            </svg>
          </a>
        </div>
      </div>
    );
  }
}

export default withRouter(ItemCard);
