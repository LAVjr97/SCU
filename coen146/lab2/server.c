//
//  Behnam Dezfouli
//  CSEN, Santa Clara University
//

// This program implements a server that accepts connection from a client and copies the received bytes to a file
//
// The input arguments are as follows:
// argv[1]: Sever's port number



#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>


int main (int argc, char *argv[]) 
{
    struct sockaddr_in {
        sa_family_t sin_family; /* address family: AF_INET */
        in_port_t sin_port; /* port in network byte order */
        struct in_addr sin_addr; /* internet address */
    };

    /* Internet address. */
    struct in_addr {
        uint32_t s_addr; /* address in network byte order */
    };

    char    message[10] = "received!";  // message to be sent to the client when the destination file name is received
    int     net_bytes_read;             // numer of bytes received over socket
    int     socket_fd = 0;              // socket descriptor
    int     connection_fd = 0;          // new connection descriptor
    struct  sockaddr_in serv_addr;      // Address format structure
    char    net_buff[1024];             // buffer to hold characters read from socket
    FILE    *dest_file;                 // pointer to the file that will include the received bytes over socket
    int     backlog = 1;
    int     size;


    if (argc < 2) // Note: the name of the program is counted as an argument
    {
        printf ("Port number not specified!\n");
        return 1;
    }

    bzero(net_buff, 1024);

    //set up struct
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = atoi(argv[1]); //sets port number to be used 
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //ip adress of home

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);  //creates a socket fd
    bind(socket_fd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
    listen(socket_fd, backlog);

    connection_fd = accept(socket_fd, (struct sockaddr *) NULL, NULL);
    read(connection_fd, net_buff, sizeof(net_buff));

    dest_file = fopen(net_buff, "w");
    bzero(net_buff, 1024);

    write(connection_fd, &message, 10);

    while((size = read(connection_fd, net_buff, sizeof(net_buff))) > 0)
        fwrite(net_buff, 10, size, dest_file);
    
    fclose(dest_file);

    close(connection_fd);
}

