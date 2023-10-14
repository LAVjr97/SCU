
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
        print 'Usage: python %s <PortNumber>' % (sys.argv[0])
        sys.exit()
    
    
    # STUDENT WORK


    # Server should be up and running and listening to the incoming connections
    while True:
        print('The server is ready to respond to incoming requests...')


        # STUDENT WORK


        try:

            # STUDENT WORK


            if (file_extension == 'html'):
                response_headers = { 'Content-Type': 'text/html; encoding=utf8' }
            elif (file_extension == 'jpg'):
                response_headers = { 'Content-Type': 'image/jpeg; encoding=utf8' }
            else:
                print 'Invalid file type, we only support html and jpg!'
                continue

            
            # STUDENT WORK


            
            
        #Raised when an I/O operation (such as a print statement, the built-in open() function or a method of a file object) fails for an I/O-related reason, e.g., "file not found" or "disk full"
        except IOError:
            # STUDENT WORK


# STUDENT WORK
