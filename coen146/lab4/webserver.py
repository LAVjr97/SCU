
# Behnam Dezfouli
# CSEN, Santa Clara University

# This program implements a simple web server that serves html and jpg files

# Input arguments:
# argv[1]: Sever's port number


from socket import *  # Import socket module
import sys            # To terminate the program
import os

if __name__ == "__main__":

    # check if port number is provided
    if len(sys.argv) != 2:
        print 'Usage: python %s <PortNumber>' % (sys.argv[0])
        sys.exit()
    
    socket_fd = socket(AF_INET, SOCK_STREAM)
    socket_fd.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
    socket_fd.bind('', sys.argv[1])
    socket_fd.listen(1)

    # STUDENT WORK

    # Server should be up and running and listening to the incoming connections
    while True:
        print('The server is ready to respond to incoming requests...')

        connection_fd, addr = socket_fd.accept()


        buff = connection_fd.recv(1024)
        fname, file_extension = os.path.splitext(buff)

        # STUDENT WORK


        try:

            file = open(fname, 'r')
            file_buff = file.read()

            if (file_extension == 'html'):
                response_headers = { 'Content-Type': 'text/html; encoding=utf8' }
            elif (file_extension == 'jpg'):
                response_headers = { 'Content-Type': 'image/jpeg; encoding=utf8' }
            else:
                print 'Invalid file type, we only support html and jpg!'
                continue

            header = 'HTTP/1.1 200 OK \nServer: SCU Web Server \n'
            content = 'Content-Length: '
            header = header + response_headers + content

            content = len(file_buff)
            header = header + content + '\n\n'

            connection_fd.sendall(header)
            connection_fd.sendall(file_buff)

            close(file)
            connection_fd.close()         
            
        #Raised when an I/O operation (such as a print statement, the built-in open() function or a method of a file object) fails for an I/O-related reason, e.g., "file not found" or "disk full"
        except IOError:
            # STUDENT WORK
            print('Error')
            


# STUDENT WORK