import React, { Component } from "react";
import clothService from "../services/clothService";
import userService from "../services/user.service";
import HistoryItemCard from "./components/history_itemCard";


export default class Profile extends Component {
  state = {
    history: [],
    historyIds: [],
  };

  componentDidMount() {
    this.init();
  }

  async init() {
    const items = await this.getHistory();
    items.forEach(async (e) => {
      const { data } = await clothService.getClothById(e);
      let carts = [...this.state.history];
      carts.push(data);
      this.setState({ history: carts });
    });
  }

  getHistory = async () => {
    const data = await userService.getHistory();
    console.log(data);
    this.setState({ historyIds: data });
    return data;
  };

  render() {

    console.log(this.state.history);
    console.log(this.state.historyIds);

    return (
      <div className="container">
        <h1 className="mt-2 mb-6 mw-xl">User History</h1>
        <div className="row align-items-center">
          <div className="border">
            {this.state.history.map((item, i) => (
              <div key={i} className="row align-items-center">
                <HistoryItemCard cloth={item} />
              </div>
            ))}
          </div>
        </div>
      </div>
    );
  }
}
