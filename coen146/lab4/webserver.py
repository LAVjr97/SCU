
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
        print ('Usage: python %s <PortNumber>' % (sys.argv[0]))
        sys.exit()
    
    socket_fd = socket(AF_INET, SOCK_STREAM)
    socket_fd.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
    socket_fd.bind(('127.0.0.1', int(sys.argv[1])))
    socket_fd.listen(1)

    # Server should be up and running and listening to the incoming connections
    while True:
        print('The server is ready to respond to incoming requests...')

        connection_fd, addr = socket_fd.accept() 
        byteBuff = connection_fd.recv(1024)
        buff = str(byteBuff, 'utf-8')

        fname = buff.split(' /')[1]
        fname = fname.split(' HTTP')[0]

        print (fname)
        
        file_extension = fname.split('.')[1]

        print(file_extension)
        try:
            print("trying")

            file = open(fname, 'r') 
            print("after opening") 
            file_buff = file.read()  
            print("after reading") 
            contentLength = str(len(file_buff)) 

            if (file_extension == 'html'):
                response_headers =  'Content-Type: text/html; encoding=utf8' 
            elif (file_extension == 'jpg'):
                response_headers =  'Content-Type: image/jpg; encoding=utf8' 
            else:
                print ('Invalid file type, we only support html and jpg!')
                continue
            print("before header")
            header = 'HTTP/1.1 200 OK \nServer: SCU Web Server \n'
            header = header + response_headers + '\nContent-Length: ' + contentLength + '\n\n'

            header = bytes(header, encoding='utf-8')
            file_buff = bytes(file_buff, encoding='utf-8')
            print("before sending")
            connection_fd.sendall(header)    
            connection_fd.sendall(file_buff) 
            
            print("before closing")
            file.close()
            connection_fd.close()         
            
        #Raised when an I/O operation (such as a print statement, the built-in open() function or a method of a file object) fails for an I/O-related reason, e.g., "file not found" or "disk full"
        except IOError:
            # STUDENT WORK
            print('Error') 

            file = open('error.html', 'r') 
            file_buff = file.read()

            contentLength = str(len(file_buff))
            header = 'HTTP/1.1 200 OK \nServer: SCU Web Server \nContent-Type: text/html \nContent-Length: ' + contentLength + '\n\n'

            header = bytes(header, encoding='utf-8')
            file_buff = bytes(file_buff, encoding='utf-8')

            connection_fd.sendall(header) 
            connection_fd.sendall(file_buff)

            file.close()
            connection_fd.close() 




            


# STUDENT WORK