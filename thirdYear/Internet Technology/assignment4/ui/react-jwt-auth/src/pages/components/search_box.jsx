import React, { Component } from "react";

class SearchBox extends Component {
  state = { text: "" };

  handleSubmit = () => {
    this.props.search(this.state.text);
  };

  render() {
    return (
      <div>
        <div className="d-none d-xl-flex mx-auto align-items-center py-3 ps-8 pe-2 border bg-white rounded-3 mb-5">
          <svg
            className="flex-shrink-0 me-2"
            style={{ width: "24px", height: "18px" }}
            width="18"
            height="18"
            viewBox="0 0 18 18"
            fill="none"
            xmlns="http://www.w3.org/2000/svg"
          >
            <path
              d="M17.5 17.1309L12.5042 11.9551"
              stroke="black"
              strokeMiterlimit="10"
              strokeLinecap="round"
              strokeLinejoin="round"
            ></path>
            <path
              d="M7.27524 13.8672C10.8789 13.8672 13.8002 10.945 13.8002 7.34033C13.8002 3.73565 10.8789 0.813477 7.27524 0.813477C3.67159 0.813477 0.750244 3.73565 0.750244 7.34033C0.750244 10.945 3.67159 13.8672 7.27524 13.8672Z"
              stroke="black"
              strokeMiterlimit="10"
              strokeLinecap="round"
              strokeLinejoin="round"
            ></path>
          </svg>
          <input
            className="form-control bg-white border-0 me-2"
            type="text"
            placeholder=""
            onChange={(e) => this.setState({ text: e.target.value })}
            onKeyDown={(e) => {
              if (e.key === "Enter") this.handleSubmit();
            }}
          />
          <button className="btn btn-info btn-sm" onClick={this.handleSubmit}>
            Search
          </button>
        </div>
      </div>
    );
  }
}

export default SearchBox;
