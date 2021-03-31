import socket
import sys
                            
sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)                        

try:
    sock.connect(("127.0.0.1", 2222))
    dane = input("Dane: ")
    sock.send(dane)
    resp = sock.recv(1024)
    print resp
    
except socket.error:
    pass


finally:
    sock.close()