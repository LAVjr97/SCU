// SCU COEN 146
//
// This program implements the server side of stop & wait protocol
// the server receives file contents from a client
//
//
// For the stop and wait protocol, the assumestions are:
//      -- packet corruption, and packet loss


#include	"tfv1.h"

// global variables
int state = 0; // we only have two states: 0 and 1
int sock;
struct sockaddr_in serverAddr;
socklen_t addr_size;


// list of functions
int main (int, char *[]);
int my_receive (PACKET *);
int calc_checksum (char *, int);



int main (int argc, char *argv[])
{
	FILE	*fp;
	int		n;
	PACKET	buf;


    if (argc != 2)
    {
        printf ("need the port number\n");
        return 1;
    }

    
    // STUDENT WORK
    serverAddr.sin_family = PF_INET;
    serverAddr.sin_port = htons(atoi(argv[1]));
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	// create socket
	if ((sock = socket (PF_INET, SOCK_DGRAM, 0)) < 0)
	{
		printf ("socket error\n");
		return 1;
	}
	printf("Socket created \n");
	// bind
	if (bind (sock, (struct sockaddr *)&serverAddr, sizeof (serverAddr)) != 0)
	{
		printf ("bind error\n");
		return 1;
	}
	printf("Socket bound \n");
    // NOTE: this program uses UDP socket, so there is no need to listen to incoming connections!
    
	// receive name of the file
    // my_receive() function ensures the received data chunks are not corrupted

	if ((n = my_receive (&buf)) <= 0)
	{
		printf ("could not get the name of the file\n");
		return 1;
	}
    printf ("File name has been received!\n");
    
	// open file
	if ((fp = fopen (buf.data, "wb")) == NULL)
	{
		printf ("error fopen\n");
		return 1;
	}

    
	printf ("Receiving file %s ... \n", buf.data);
    // my_receive() function ensures the received data chunks are not corrupted
	while ((n = my_receive (&buf)) > 0)
	{
		printf ("writing to file... n = %d\n", n);
        fwrite(&buf.data, 1, n, fp);
	}

	close (sock);
	fclose (fp);

	return 0;
}



// my_receive() function ensures the received data chunks are not corrupted
int my_receive (PACKET *recv_pck)
{
    int cs_in;
	int cs_calc;
	int	d;
	int r;
	int nbytes;

	HEADER			ack_packet;
	struct sockaddr	ret_addr;
	socklen_t		addr_size = sizeof (ret_addr);


	while (1)
	{
        // ssize_t recvfrom(int socket, void *restrict buffer, size_t length,
        //          int flags, struct sockaddr *restrict address, socklen_t *restrict address_len);
        // buffer: Points to the buffer where the message should be stored.
        // address: A null pointer, or points to a sockaddr structure in which the sending address is to be stored.
        // The length and format of the address depend on the address family of the socket.
        // address_len: Specifies the length of the sockaddr structure pointed to by the address argument.
		if ((nbytes = recvfrom (sock, recv_pck, sizeof(PACKET), 0, &ret_addr, &addr_size)) < 0){
			return -1;
		}
		        
		printf ("Received a UDP packet!\n");
        
		cs_in = recv_pck->header.checksum;
		recv_pck->header.checksum = 0;
        
        // recalculate checksum 
		
		int bytesize = sizeof(HEADER) + recv_pck -> header.len;
		cs_calc = calc_checksum((char *)&recv_pck, bytesize);
			
        // check if checksum matches, and the sequence number is correct too
        if (cs_in == cs_calc  &&  recv_pck->header.seq_ack == state)
		{
            printf ("Checksum passed! Sequence number matched!\n");

			// good packet
			ack_packet.seq_ack = state;
			ack_packet.len = 0;
            
            // simulating erroneous channel...corruption and loss
			r = rand () % 10;
    		if (r > 8){
        		ack_packet.checksum = 0; 
				printf ("Packet got corrupted on the way!\n");
			}
			else	
				ack_packet.checksum = calc_checksum((char *)&ack_packet, sizeof(ack_packet));

			r = rand () % 10;
			if(r > 8)
				printf("Packet was lost on the way\n");
			else
				//packet is being sent, but can have its checksum corrupted
				sendto(sock, &ack_packet, sizeof(HEADER), 0, (struct sockaddr *) &ret_addr, sizeof(ret_addr));

			// now we are expecting the next packet
            if(state == 0) 
				state = 1;
			else 
				state = 0;
            
			return recv_pck->header.len;
		}
		else
		{
            printf ("Checksum/sequence number check failed!\n");

			// bad packet
			int nstate;

			if(state == 0)
				nstate = 1;
			else 
				nstate = 0; 

			ack_packet.seq_ack = nstate;
			ack_packet.len = 0;
			ack_packet.checksum = calc_checksum((char *)&ack_packet, sizeof(ack_packet));
            printf ("Resending ack for sequence number: %d...\n", ack_packet.seq_ack );

            
            // simulating erroneous channel...corruption and loss
			r = rand () % 10;
    		if (r > 8){
        		ack_packet.checksum = 0; 
				printf ("Packet got corrupted on the way!\n");
			}

			r = rand () % 10;
			if(r > 8)
				printf("Packet was lost on the way\n");
			else
				//packet is being sent, but can have its checksum corrupted
				sendto(sock, &ack_packet, sizeof(HEADER), 0, (struct sockaddr *) &ret_addr, sizeof(ret_addr));
			
		}

	}

	return -1;
}



int calc_checksum (char *buf, int tbytes)
{
    int		i;
    char	cs = 0;
    char 	*p;

	cs = cs ^ tbytes;

    return (int)cs;
}

