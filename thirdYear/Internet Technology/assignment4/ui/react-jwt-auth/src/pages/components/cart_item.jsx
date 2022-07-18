import React, { Component } from "react";


class CartItemCard extends Component {
  render() {
    const {
      item: { cloth, quantity },
      updateCart,
    } = this.props;

    return (
      <div>
        <div>
          <div className="row align-items-center">
            <div className="col-12 col-md-8 col-lg-6 mb-6 mb-md-0">
              <div className="row align-items-center">
                <div className="col-12 col-md-4 mb-3">
                  <div
                    className="d-flex align-items-center justify-content-center bg-light"
                    style={{ width: "96px", height: "128px" }}
                  >
                    <img
                      className="img-fluid"
                      style={{ objectFit: "contain" }}
                      src={cloth.images[0]}
                      alt=""
                    />
                  </div>
                </div>
                <div className="col-8">
                  <h3 className="mb-2 lead fw-bold">{cloth.name}</h3>
                  <p
                    className="mb-0 text-secondary"
                    // dangerouslySetInnerHTML={true}
                    dangerouslySetInnerHTML={{
                      __html:
                        cloth.shortDescription ||
                        cloth.description.substr(0, 65) + "...",
                    }}
                  ></p>
                </div>
              </div>
            </div>
            <div className="d-none d-lg-block col-lg-2">
              <p className="mb-0 lead fw-bold text-info">
                ₹{Math.round(cloth.price * ((100 - cloth.discount) * 0.01))}
              </p>
              <span className="small text-secondary text-decoration-line-through">
                ₹{cloth.price}
              </span>
            </div>
            <div className="col-auto col-md-2">
              <div className="d-inline-flex align-items-center px-4 fw-bold text-secondary border rounded-2">
                <button
                  className="btn px-0 py-2"
                  onClick={() => {
                    if (quantity > 1) updateCart(cloth.id, quantity - 1);
                  }}
                >
                  <svg
                    width="12"
                    height="2"
                    viewBox="0 0 12 2"
                    fill="none"
                    xmlns="http://www.w3.org/2000/svg"
                  >
                    <g opacity="0.35">
                      <rect
                        x="12"
                        width="2"
                        height="12"
                        transform="rotate(90 12 0)"
                        fill="currentColor"
                      ></rect>
                    </g>
                  </svg>
                </button>
                <input
                  className="form-control px-2 py-4 text-center text-md-end border-0"
                  style={{ width: "48px" }}
                  type="number"
                  placeholder={quantity}
                  disabled
                />
                <button
                  className="btn px-0 py-2"
                  onClick={() => {
                    updateCart(cloth.id, quantity + 1);
                  }}
                >
                  <svg
                    width="12"
                    height="12"
                    viewBox="0 0 12 12"
                    fill="none"
                    xmlns="http://www.w3.org/2000/svg"
                  >
                    <g opacity="0.35">
                      <rect
                        x="5"
                        width="2"
                        height="12"
                        fill="currentColor"
                      ></rect>
                      <rect
                        x="12"
                        y="5"
                        width="2"
                        height="12"
                        transform="rotate(90 12 5)"
                        fill="currentColor"
                      ></rect>
                    </g>
                  </svg>
                </button>
              </div>
            </div>
            <div className="col-auto col-md-2 text-end">
              <p className="lead fw-bold text-info">
                ₹
                {Math.round(cloth.price * ((100 - cloth.discount) * 0.01)) *
                  quantity}
              </p>
            </div>
          </div>
        </div>
      </div>
    );
  }
}

export default CartItemCard;
