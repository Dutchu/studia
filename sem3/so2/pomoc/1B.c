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
#include <sys/file.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <signal.h>

int main(int argc, char **argv){

    int fd;
    int pid;

    if ((fd = open("/var/run/lock/proces.lock", O_RDWR | O_CREAT, 0666)) == -1){

        printf("can't open file");
        exit(1);

    }

    int lock = flock(fd, LOCK_EX | LOCK_NB);

    if(lock == -1){

        char *new_so = getenv("SO2");
        if(new_so == NULL){
           printf("uruchomiony inny proces"); 
	   exit(1);
        }

        if(strcmp(new_so,"NEW") == 0){

            FILE *plik = fopen("/var/run/lock/proces.lock","r");
            if(plik != NULL){
                fscanf(plik,"%d",&pid);
                fclose(plik);
                printf("\n");
		kill(pid, SIGKILL);
                printf("\n");
		while(flock(fd, LOCK_EX | LOCK_NB) != 0);
            }else{
                printf("brak dostepu do pliku");
                exit(1);
            }
        }
        else{
            printf("Inny proces jest uruchomiony.");
            exit(1);
        }
    }

    FILE * plik = fopen("/var/run/lock/proces.lock","w");
    if(plik != NULL){
        fprintf(plik, "%d", getpid());
        fclose(plik);
    }else{
        printf("brak dostepu do pliku");
        exit(1);
    }

    printf("Uruchomiono proces z pid=%d", getpid());

    getchar();

    return 0;
}
