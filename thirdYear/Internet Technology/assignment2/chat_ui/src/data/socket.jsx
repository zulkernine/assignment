import { io } from "socket.io-client";

const socket = io("http://192.168.43.218:3075/");

export default socket;
