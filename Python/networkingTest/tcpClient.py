# A script that is used to test ping a website and grab its content
import socket
target_host = "192.168.0.4"
target_port = 80

client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((target_host,target_port))
client.send("GET /index.php HTTP/1.1\r\nHost: 192.168.0.4\r\n\r\n")
response = client.recv(4096)
print response
