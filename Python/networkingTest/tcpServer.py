# A simple TCP server developed while learning how to use Python sockets
import socket
import threading

bIp = "0.0.0.0"
bPort = 9999

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server.bind((bIp,bPort))

server.listen(5)

print"[*] listening on %s:%d" % (bIp,bPort)
def handle_client(client_socket):

  request = client_socket.recv(1024)

  print "[*] Received: %s" % request

  client_socket.send("ACK!")

  client_socket.close()

while True:
  client,addr = server.accept()
  print "[*] Accepted connection from: %s:%d" % (addr[0],addr[1])
  client_handler = threading.Thread(target=handle_client,args=(client,))
  client_handler.start()
