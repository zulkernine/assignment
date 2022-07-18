import React, { Component } from "react";
import clothService from "../services/clothService";
import { ReactComponent as Star } from "../yofte-assets/elements/star-gold.svg";
import { ReactComponent as GreyStar } from "../yofte-assets/elements/star-gray.svg";
import MyEvent from "../services/my_event";
import KEY from "../KEY.json";
import userService from "../services/user.service";

class ProductPage extends Component {
  componentDidMount() {
    this.state.id = this.props.match.params.id;
    this.state.loading = false;
    this.loadCloths();
  }

  handleAddtoCart = async () => {
    const id = this.props.match.params.id;
    await this._addToUserCart(id);
    MyEvent.fire(KEY.AddedToCart);
  };

  _addToUserCart = async (id) => {
    await userService.addToCart(id);
  };

  async loadCloths() {
    this.setState({ loading: true });

    let { data: c } = await clothService.getClothById(this.state.id);

    this.setState({ product: c, loading: false });
    // console.log(c);
  }
  state = { id: "", product: null, loading: false, imageIndex: 0 };

  createStarRating = (rating) => {
    const r = Math.round(rating);
    let stars = [];
    for (let i = 0; i < r; i++) {
      stars.push(
        <button className="btn p-0">
          <Star />
        </button>
      );
    }
    for (let i = 0; i < 5 - r; i++) {
      stars.push(
        <button className="btn p-0">
          <GreyStar />
        </button>
      );
    }

    return stars;
  };

  render() {
    const { product, imageIndex, loading } = this.state;

    if (product == null || loading)
      return (
        <div className="spinner-grow text-primary" role="status">
          <span className="sr-only">Loading...</span>
        </div>
      );

    return (
      <div className="">
        <section className="py-20 overflow-hidden">
          <div className="container">
            <div className="row mb-24">
              <div className="col-12 col-md-6 mb-8 mb-md-0">
                <div
                  className="position-relative mb-10"
                  style={{ height: "564px" }}
                >
                  <a
                    className="position-absolute top-50 start-0 ms-8 translate-middle-y"
                    href="#"
                  ></a>
                  <img
                    className="img-fluid w-100 h-100"
                    style={{ objectFit: "contain" }}
                    src={product.images[imageIndex]}
                    alt=""
                  />
                  <a
                    className="position-absolute top-50 end-0 me-8 translate-middle-y"
                    href="#"
                  ></a>
                </div>
                <div className="row mx-1">
                  {product.images.map((e, i) => (
                    <div className="col-6 col-sm-3 p-2" key={i}>
                      <a
                        className="d-block border border-info"
                        href="#"
                        onClick={() => {
                          this.setState({ imageIndex: i });
                        }}
                      >
                        <img
                          className="w-100 img-fluid"
                          style={{ height: "128px" }}
                          src={e}
                          alt=""
                        />
                      </a>
                    </div>
                  ))}
                </div>
              </div>
              <div className="col-12 col-md-6">
                <div className="ps-lg-20">
                  <div className="mb-10 pb-10 border-bottom">
                    <span className="text-secondary">
                      {product.categories[0]}
                    </span>
                    <h1 className="mt-2 mb-6 mw-xl">{product.name}</h1>
                    <div className="mb-8">
                      {this.createStarRating(product.rating)}
                      <p className="d-inline-block mb-8 h6 text-info">
                        ({product.rating})
                      </p>
                    </div>
                    <p className="d-inline-block mb-8 h5 text-info">
                      <span>
                        ₹
                        {Math.round(
                          product.price * ((100 - product.discount) * 0.01)
                        )}
                      </span>
                      <span
                        className="fw-normal text-secondary text-decoration-line-through"
                        style={{ fontSize: "16px" }}
                      >
                        {product.price}
                      </span>
                    </p>
                    <p className="mw-md text-secondary">
                      {product.shortDescription}
                    </p>
                  </div>
                  <div className="d-flex mb-12">
                    <div>
                      <span className="d-block mb-4 fw-bold text-secondary text-uppercase">
                        Size
                      </span>
                      <select
                        className="form-select border ps-6 pe-10 py-4 fw-bold text-secondary"
                        name=""
                        id=""
                      >
                        {product.availableSize.map((e, i) => (
                          <option value={e} key={i}>
                            {e}
                          </option>
                        ))}
                      </select>
                    </div>
                  </div>
                  <div className="row mb-14">
                    <div className="col-12 col-xl-8 mb-4 mb-xl-0">
                      <a
                        className="btn w-100 btn-primary"
                        href="#"
                        onClick={this.handleAddtoCart}
                      >
                        Add to cart
                      </a>
                    </div>
                    <div className="col-12 col-xl-4">
                      <a
                        className="flex-shrink-0 h-100 d-inline-flex align-items-center justify-content-center rounded-2 border"
                        href="#"
                        style={{ width: "64px", minHeight: "52px" }}
                      ></a>
                    </div>
                  </div>
                  <div className="d-flex align-items-center">
                    <p className="me-8 mb-0 text-secondary fw-bold text-uppercase">
                      SHARE IT
                    </p>
                    <a
                      className="me-1"
                      href="#"
                      style={{ width: "32px", height: "32px" }}
                    >
                      <img
                        className="img-fluid"
                        src="yofte-assets/buttons/facebook-circle.svg"
                        alt=""
                      />
                    </a>
                    <a
                      className="me-1"
                      href="#"
                      style={{ width: "32px", height: "32px" }}
                    >
                      <img
                        className="img-fluid"
                        src="yofte-assets/buttons/instagram-circle.svg"
                        alt=""
                      />
                    </a>
                    <a href="#" style={{ width: "32px", height: "32px" }}>
                      <img
                        className="img-fluid"
                        src="yofte-assets/buttons/twitter-circle.svg"
                        alt=""
                      />
                    </a>
                  </div>
                </div>
              </div>
            </div>
            <div>
              <div className="row mb-16 border-bottom border-2">
                <div className="col-6 col-md-auto">
                  <a
                    className="btn bg-white text-secondary rounded-0 shadow"
                    href="#"
                  >
                    Description
                  </a>
                </div>
                <div className="col-6 col-md-auto"></div>
                <div className="col-6 col-md-auto"></div>
                <div className="col-6 col-md-auto"></div>
              </div>
              <h3 className="mb-8 text-info">
                Summer collection and laoreet get
              </h3>
              <p
                className="mw-2xl text-secondary"
                dangerouslySetInnerHTML={{ __html: product.description }}
              ></p>
            </div>
          </div>
        </section>
      </div>
    );
  }
}

export default ProductPage;
