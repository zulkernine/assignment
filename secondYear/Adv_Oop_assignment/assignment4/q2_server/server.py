import socket
import threading
from hashlib import sha256

#Global variables
UDP_IP_ADDRESS = "127.0.0.1"
UDP_PORT_NO = 6789
global_lock = threading.Lock()

#Main task of the sever
def server_task(client_socket):
    while True :
        data = client_socket.recv(1024)
        if not data :
            client_socket.send(b"Thanks for using our service!")
            print("Terminating server thread: ",threading.current_thread().name)
            global_lock.release()
            break
        hashed_value = sha256(str(data).encode("utf-8")).hexdigest().encode("utf-8")
        client_socket.send(hashed_value)
    client_socket.close()

#server running code


def server_main():
    serverSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    serverSock.bind((UDP_IP_ADDRESS, UDP_PORT_NO))
    serverSock.listen(8)
    print("Server is now listeing!")

    while True:
        c, addr = serverSock.accept()
        # data, addr = serverSock.recvfrom(1024)
        print('Got connection from', addr)
        global_lock.acquire()
        thr = threading.Thread(target=server_task, args=(c,))
        thr.start()

    serverSock.close()

#Run the server
if __name__ == '__main__' :
    server_main()


