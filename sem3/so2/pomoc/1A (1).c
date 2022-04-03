#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sched.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <linux/sched.h>
#include <sys/types.h> 

#define SIZESTACK (1024 * 1024)

int DisplayID(void *arg){

   char *argument = (char *) arg;

   printf("Argument przekazany do clone = %s, pid = %d\n", argument, getpid());

}

int main(int argc, char **argv){

   char *stack;
   char *stackhead;

   if(argc < 2){
      printf("Program launched with no Arguments\n");
      return 0;
   }
   //CLONE
   if(*(argv[1]) == 'c') {

       stack = malloc(SIZESTACK);

       if (!stack) {
           printf("blad alokacji\n");
           exit(1);
       }

       stackhead = stack + SIZESTACK - 1;
       for (int i = 1; i < argc; i++) {
           int cloneid = clone(DisplayID, stackhead, SIGCHLD, argv[i]);

           if (cloneid == -1) {
               printf("Ni mo clone\n");
               exit(1);
           }
       }
       free(stack);
   }
   //FORK
   else{
       for(int i = 1; i < argc; i++){

           int pid = fork();

           if (pid == 0){ 
		   printf("argument %s: PID Potomka: %d\n", argv[i], getpid());
		   exit(0);
	   }

         }
       }
      return 0;
}
