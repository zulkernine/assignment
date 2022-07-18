import React, { Component } from "react";
import clothService from "../services/clothService";
import ItemCard from "./components/item_card";
import SearchBox from "./components/search_box";

export default class Home extends Component {
  constructor(props) {
    super(props);

    this.state = {
      content: [],
      pageNo: 1,
      search: "",
    };
  }

  componentDidMount() {
    this.fetchAllClothes(1);
  }

  fetchAllClothes(pageNo = this.state.pageNo, text) {
    clothService
      .searchPublicContent(text ? text : this.state.search, pageNo)
      .then(
        (response) => {
          const c = [...this.state.content, ...response.data];

          this.setState({
            content: c,
          });
          console.log(response.data);
        },
        (error) => {
          this.setState({
            content:
              (error.response && error.response.data) ||
              error.message ||
              error.toString(),
          });
        }
      );
  }

  getMoreClothes = () => {
    let p = this.state.pageNo;
    this.fetchAllClothes(p + 1);
    this.setState({ pageNo: p + 1 });
  };

  handleSearch = async (text) => {
    if (text != this.state.search) {
      this.setState({ search: text, pageNo: 1,content:[] });
      this.fetchAllClothes(1,text);
    }

    // const { data } = await clothService.searchPublicContent(text);
    // console.log(data);
  };

  render() {
    return (
      <section className="py-20 bg-light overflow-hidden" id="products">
        <div className="container">
          <SearchBox search={this.handleSearch} />
          <h2 className="mb-16 mb-md-24">Discover our products</h2>
          <div className="row mb-24">
            {this.state.content.map((e) => (
              <div className="col-12 col-md-6 col-lg-4 mb-6" key={e["id"]}>
                <ItemCard cloth={e} />
              </div>
            ))}
          </div>
          <div className="text-center">
            <div
              className="btn btn-primary"
              href="#"
              onClick={this.getMoreClothes}
            >
              Show More
            </div>
          </div>
        </div>
      </section>
    );
  }
}
