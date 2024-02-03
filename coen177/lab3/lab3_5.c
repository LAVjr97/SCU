// Name: Luis Villalta
// Date: 2/3/24
// Title: Lab 3: Step 5
// Description: Creates two processes where one is a producer with a buffer size of 50 which then passes 
//              its message through the pipe to the consumer, which reads the message only 10 characters at a time
//              by clearing its buffer after each time it reads from its input. 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/wait.h> 

// main
int main(int argc,char *argv[]){
   int  fds[2];
   char buffer[50];
   char buff[11];
   int count;
   int i = 0, j, size;
   pipe(fds);
   
   if (fork()==0){
       close(fds[0]);
       printf("Message sent by producer: \n");
       scanf("%s", buffer);
       write(fds[1], buffer, strlen(buffer)); 
       exit(0);
    }
   else if(fork()==0){
       close(fds[1]);
       while((count=read(fds[0],buff, sizeof(buff) - 1)) > 0){
         buff[10] = '\0';              //gets rid of the garbage values being passed
         printf("Consumer: \n");
         write(1,buff,strlen(buff));
         printf("\n");
         memset(buff, '\0', sizeof(buff));   //clears the buffer
       }
       exit(0);
    }
   else{     
      close(fds[0]);
      close(fds[1]);
      wait(0);
      wait(0);
   }
return 0;
}
