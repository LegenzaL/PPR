import socket
import sys
   
ip = "127.0.0.1"
port = 20000
message = raw_input("Message: ")
   
print("UDP target IP: %s" % ip)
print("UDP target port: %s" % port)
print("message: %s" % message)
  
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.sendto(message, (ip, port))    
