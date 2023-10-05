//
//  Behnam Dezfouli
//  CSEN, Santa Clara University
//

// This program implements a client that connects to a server and transfers the bytes read from a file over the established connection
//
// The input arguments are as follows:
// argv[1]: Sever's IP address
// argv[2]: Server's port number
// argv[3]: Source file
// argv[4]: Destination file at the server side which includes a copy of the source file



#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#define    SIZE 10

int main (int argc, char *argv[])
{
    int        sockfd = 0;              // socket descriptor
    char       net_buff[SIZE];          // to hold the bytes read from socket
    char       file_buff[SIZE];         // to hold the bytes read from source file
    struct     sockaddr_in serv_addr;   // server address structure
    int        net_bytes_read;          // numer of bytes received over socket
    FILE       *source_file;            // pointer to the source file
    
    if (argc < 5)
    {
        printf ("Usage: ./%s <server ip address> <server port number> <source file>  <destination file>\n", argv[0]);
        return 1;
    }
    
    // Make sure intial values are zero
    memset (net_buff, '0', sizeof (net_buff));
    memset (file_buff, '0', sizeof (file_buff));
    memset (&serv_addr, '0', sizeof (serv_addr));
        
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2])); //sets port number to be used 
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //ip adress of home
    
    sockfd = socket(AF_INET, SOCK_STREAM, 0);  //creates a socketfd 
    
    connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    printf("Connection Established \n"); 

    //Writes the name of the destination file to the socket
    write(sockfd, argv[4], strlen(argv[4]) + 1); 

    source_file = fopen(argv[3], "r");
    printf("File Name Sent \n");

    //Writes the source file to the socket
    while((net_bytes_read = fread(file_buff, 1, sizeof(file_buff), source_file)) > 0)
        write(sockfd, file_buff, net_bytes_read); 
    
    printf("File Sent! \n");

    fclose(source_file);
    close(sockfd);
    return 0; 
}

