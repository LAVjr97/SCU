
# Behnam Dezfouli
# CSEN, Santa Clara University

# This program implements a simple web server that serves html and jpg files

# Input arguments:
# argv[1]: Sever's port number


from socket import *  # Import socket module
import sys            # To terminate the program

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
        buff = str(byteBuff) #converts the binary recieved into a string 
        print('\nRecieved HTTP request: \n' + buff) 

        try:
            fname = buff.split('/')[1] #splits the HTTP request message and stores the name of the file requested with ' HTTP' attached to it
            
            if(fname == ' HTTP'): #if fname only has ' HTTP' that means no file was specified in the HTTP request header.
                fname = 'index-1.html' 
                file_extension = 'html' 

            else:
                fname = fname.split(' HTTP')[0] #gets rid of the 'HTTP' that was next to the file name 
                file_extension = fname.split('.')[1] #gets the file extension

            if (file_extension == 'html'):
                response_headers =  'Content-Type: text/html; encoding=utf8' 
            elif (file_extension == 'jpg'):
                response_headers =  'Content-Type: image/jpg; encoding=utf8' 
            else:
                print ('Invalid file type, we only support html and jpg!') 
                continue

            file = open(fname, 'rb') #opens the file to be read as binary 
            file_buff = file.read()  #stores the file into a buffer

            contentLength = str(len(file_buff)) 

            header = 'HTTP/1.1 200 OK \nServer: SCU Web Server \n' + response_headers + '\nContent-Length: ' + contentLength + '\n\n'
            print('HTTP Header Sent to Client: \n' + header)
            
            header = bytes(header) #converts the string header into a bytes object
            header = header + file_buff 

            connection_fd.sendall(header) 
            
            file.close()
            connection_fd.close()         
            
        #Raised when an I/O operation (such as a print statement, the built-in open() function or a method of a file object) fails for an I/O-related reason, e.g., "file not found" or "disk full"
        except IOError:

            print('Error') 

            file = open('error.html', 'rb') 
            file_buff = file.read() 
            contentLength = str(len(file_buff))

            header = 'HTTP/1.1 404 OK \nServer: SCU Web Server \nContent-Type: text/html \nContent-Length: ' + contentLength + '\n\n'            
            header = bytes(header) #converts the string header into a bytes object

            header = header + file_buff 

            connection_fd.sendall(header) 

            file.close()
            connection_fd.close()