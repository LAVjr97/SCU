// Name: Luis Villalta
// Date: 2/3/24
// Title: Lab 3: Step 4
// Description: Creates two processes to handle a system call " cat /etc/passwd" and passing it through a pipe to
//              the other process that handles another system call "grep root" 
//              handles the response and formats it with spaces in between each character. 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/wait.h> 

// main
int main(int argc,char *argv[]){
   int  fds[2];
   char buff[60];
   int count;
   int i;
   pipe(fds);
   
   if (fork()==0){
       dup2(fds[1], 1);
		 close(fds[1]);
       execlp("cat", "cat", "/etc/passwd", NULL);

       exit(0);
   }
   
   else if(fork()==0){
       dup2(fds[0], 0);
		 close(fds[0]);
       execlp("grep", "grep", "root", NULL);
      
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
