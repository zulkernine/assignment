import axios from "axios";
import authHeader from "./auth-header";

import config from "../config.json";

const API_URL = config.base_url_user;

class UserService {
  getUserBoard() {
    return axios.get(API_URL, { headers: authHeader() });
  }

  addToCart(id) {
    return axios.post(API_URL + "cart/" + id, {}, { headers: authHeader() });
  }

  async getCartList() {
    const { data: user } = await this.getUserBoard();
    return user.cart;
  }

  async getHistory() {
    const { data: user } = await this.getUserBoard();
    return user.history;
  }

  checkout(avg) {
    return axios.get(API_URL + "checkout", {
      headers: authHeader(),
      params: { average: avg },
    });
  }
}

export default new UserService();
