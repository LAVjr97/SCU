/**************************
*   Lab3 - Producer - Consumer
**************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/wait.h> 

// main
int main(int argc,char *argv[]){
   int  fds[2];
   char buffer[30] = "012345678901234567890123456789";
   char buff[10];
   int count;
   int i, j;
   pipe(fds);
   
   if (fork()==0){
       printf("\nWriter on the upstream end of the pipe -> %d arguments \n",argc);
       close(fds[0]);
       printf("Message to be sent by producer: \n");
       scanf("%d", &buffer);
       write(fds[1],buffer[i],strlen(buffer[i]));
       
       exit(0);
   }
   else if(fork()==0){
       printf("\nReader on the downstream end of the pipe \n");
       close(fds[1]);
       printf("Message recieved by consumer:")

       while((count=read(fds[0],buff,10))>0){
         write(1,buff+i,1);
         printf("\n");
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
