import socket
import sys

sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

server_address = ('localhost', 20000)
sock.connect(server_address)

try:
    
    message = raw_input("Message:\n")
    
    sock.sendall(message)
    data = sock.recv(100)
    print 'received "%s"' % data

finally:
    sock.close()