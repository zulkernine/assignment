import axios from "axios";


const http = axios.create({
  baseURL: "http://192.168.43.218:5000/",
  timeout: 20000,
  headers: { "X-Custom-Header": "foobar" },
});

async function getAllUsers(){
    return (await http.get("/users")).data;
}

export {
    getAllUsers
};
