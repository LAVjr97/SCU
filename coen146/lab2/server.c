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
    serv_addr.sin_port = htons(atoi(argv[1])); //sets port number to be used 
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); //ip adress of home

    socket_fd = socket(AF_INET, SOCK_STREAM, 0);  //creates a socket fd
    if(bind(socket_fd, (const struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
        perror("CANNOT BIND\n");

    listen(socket_fd, backlog);

    if((connection_fd = accept(socket_fd, (struct sockaddr *)NULL, NULL))<0)
        perror("CONNECTION REFUSED\n");
    
    printf("Connection Establsihed %d\n",connection_fd);

    //Takes name in from the socket
    read(connection_fd, net_buff, sizeof(net_buff));
    printf("File Name Recieved \n");
    if ((dest_file = fopen(net_buff, "w")) == NULL)
        perror("dest_file NOT CREATED\n");
    
    //Resets the buffer
    bzero(net_buff, 1024);

    //Copies file from socket
    while((net_bytes_read = read(connection_fd, net_buff, sizeof(net_buff))) > 0)
        fwrite(net_buff, 1, net_bytes_read, dest_file);

    printf("File Recieved! \n");    
    fclose(dest_file);
    close(connection_fd); 
}