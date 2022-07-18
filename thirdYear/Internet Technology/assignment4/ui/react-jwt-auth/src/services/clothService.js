import axios from "axios";
import authHeader from "./auth-header";

import config from "../config.json";

const API_URL = config.base_url_cloth;

class ClothService {
  getPublicContent(pageNo = 1) {
    return axios.get(API_URL, {
      params: {
        pageNo: pageNo,
      },
      headers: authHeader(),
    });
  }

  searchPublicContent(text,pageNo = 1) {
    return axios.get(API_URL, {
      params: {
        pageNo: pageNo,
        search: text,
      },
      headers: authHeader(),
    });
  }

  getClothById(id) {
    return axios.get(API_URL + id, { headers: authHeader() });
  }
}

export default new ClothService();
