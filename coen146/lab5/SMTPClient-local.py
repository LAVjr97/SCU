
# Behnam Dezfouli
#  CSEN, Santa Clara University

# This program implements a simple smtp mail client to send an email to a local smtp server

# Note:
# Run a local smtp mail server using the following command before running this code:
# python -m smtpd -c DebuggingServer -n localhost:6000


from socket import *
import ssl


# Choose a mail server
mailserver = 'localhost'


# Create socket called clientSocket and establish a TCP connection with mailserver
clientSocket = socket(AF_INET, SOCK_STREAM)

# Port number may change according to the mail server
#like the bind funtion but instead takes the ip addr and port number as a tuple
port = 6000
addr = (mailserver, port)
clientSocket.connect(addr)


recv = clientSocket.recv(1024).decode()
print(recv)
if recv[:3] != '220':
    print('220 reply not received from server.')


# Send HELO command along with the server address
HELO = 'HELO localhost:8080\r\n'
HELO = bytes(HELO)

clientSocket.sendall(HELO)
recv = clientSocket.recv(1024).decode()
print(recv)

# Send MAIL FROM command and print server response
MAIL_FROM = "MAIL FROM: lvillalta@scu.edu\r\n"
MAIL_FROM = bytes(MAIL_FROM)

clientSocket.sendall(MAIL_FROM)
recv = clientSocket.recv(1024).decode()

print(recv)

# Send RCPT TO command and print server response
# STUDENT WORK
RCPT_TO = 'RCPT TO: lvillalta@scu.edu\r\n'
RCPT_TO = bytes(RCPT_TO)

clientSocket.sendall(RCPT_TO)
recv = clientSocket.recv(1024).decode()
print(recv)

# Send DATA command and print server response
# STUDENT WORK
DATA = 'DATA\r\n'
DATA = bytes(DATA)

clientSocket.sendall(DATA)
recv = clientSocket.recv(1024).decode()
print(recv)

# Send message data. 
# STUDENT WORK 
MSG_DATA = 'SUBJECT: Hello World\r\n Line 1\n Line 2\n Last Line\n'
MSG_DATA = bytes(MSG_DATA)

# Message to send
# STUDENT WORK
clientSocket.sendall(MSG_DATA)

# Message ends with a single period
# STUDENT WORK
MSG_DATA = '\r\n.\r\n'
MSG_DATA = bytes(MSG_DATA)

clientSocket.sendall(MSG_DATA)
recv = clientSocket.recv(1024).decode()
print(recv)

# Send QUIT command and get server response
# STUDENT WORK
QUIT = 'QUIT\r\n'
QUIT = bytes(QUIT)

clientSocket.sendall(QUIT)
recv = clientSocket.recv(1024).decode()
print(recv)
