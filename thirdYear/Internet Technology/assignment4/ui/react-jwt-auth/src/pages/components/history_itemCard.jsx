import React, { Component } from 'react';
import { withRouter } from 'react-router-dom';

class HistoryItemCard extends Component {
  gotoProductPagr = (id) => {
    this.props.history.push("/product/" + id);
  };

  render() {
    const { cloth } = this.props;

    return (
      <div
        className="row align-items-center"
        onClick={() => {
          this.gotoProductPagr(cloth["id"]);
        }}
        style={{cursor:"pointer"}}
      >
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
        <div className="d-none d-lg-block col-lg-2">
          <button className="btn w-100 btn-primary">View</button>
        </div>
      </div>
    );
  }
}
 
export default withRouter(HistoryItemCard);
