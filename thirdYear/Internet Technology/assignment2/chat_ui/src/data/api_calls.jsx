import axios from "axios";
import config from "../config.json";

const http = axios.create({
  baseURL: config.server_base,
  timeout: 20000,
  headers: { "X-Custom-Header": "foobar" },
});

async function getAllUsers(){
    return (await http.get("/users")).data;
}

export {
    getAllUsers
};
