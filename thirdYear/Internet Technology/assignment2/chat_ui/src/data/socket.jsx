import { io } from "socket.io-client";
import config from "../config.json";


const socket = io(config.server_base);

export default socket;
