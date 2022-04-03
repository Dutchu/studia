#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <sys/file.h> /*open() flock()*/
#include <fcntl.h>    /*file descriptor flag changeing*/
#include <string>
#include <signal.h> /*signal to kill*/

#define PID_F_PATH "/var/run/lock/pid_lock_file"
#define BUFF_SIZE 100
#define NEW_PROCESS "NEW"
#define ENV_KEY "SO2"

#define CPF_CLOEXEC 1 /*for creating pid file*/

int lockReg(int fd, int type, int whence, int start, off_t len)
{
    struct flock fl;
    fl.l_type = type;
    fl.l_whence = whence;
    fl.l_start = start;
    fl.l_len = len;
    return fcntl(fd, F_SETLK, &fl);
}

int create_pid_file(const char *prog_name, const char *pid_file, int flags)
{
    std::cout << "Creating a file" << '\n';
    int fd;
    char buff[BUFF_SIZE];

    fd = open(pid_file, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd == -1)
    {
        throw std::runtime_error("Could not open PID file " + std::string(pid_file) + ".");
    }

    if (flags & CPF_CLOEXEC)
    {
        flags = fcntl(fd, F_GETFD);
        if (flags == -1)
            throw std::runtime_error("Could not get flags for PID file " + std::string(pid_file) + ".");

        flags |= FD_CLOEXEC;

        if (fcntl(fd, F_SETFD, flags) == -1)
            throw std::runtime_error("Could not set flags for PID file " + std::string(pid_file) + ".");
    }

    if (lockReg(fd, F_WRLCK, SEEK_SET, 0, 0) == -1)
    {
        if (errno == EAGAIN || errno == EACCES)
            throw std::runtime_error("PID file " + std::string(pid_file) + "is locked; probably " + std::string(prog_name) + " is already running.");
        else
            throw std::runtime_error("Unable to lock PID file " + std::string(pid_file) + ".");
    }

    if (ftruncate(fd, 0) == -1)
        throw std::runtime_error("Unable to lock PID file " + std::string(pid_file) + ".");

    snprintf(buff, BUFF_SIZE, "%ld\n", (long)getpid());
    if (write(fd, buff, strlen(buff)) != strlen(buff))
        throw std::runtime_error("Writing to PID file " + std::string(pid_file) + ".");

    return fd;
}

int main(int argc, char **argv)
{
    int fd;
    int res;
    char *env_key = getenv(ENV_KEY);
    if (env_key == NULL)
    {
        env_key = (char *) malloc(sizeof(char));
        *env_key = '\n';
    }
    std::string str_val_env(env_key);
    std::string str_new(NEW_PROCESS);

    if (str_new.compare(str_val_env) == 0)
    {
        std::cout << "New process" << '\n';
        char buff[BUFF_SIZE];

        int fd = open(PID_F_PATH, O_RDONLY); /*"open read only file with linux function"*/
        if (fd == -1)
        {
            std::cout << "Couldn't open file." << '\n';
            std::cout << "New process will create file." << '\n';
            goto createfile;
        }

        if (read(fd, buff, 5) != 5) /*read file to get PID of process that closed file*/
            throw std::runtime_error("Couldn't read from PID file pid_lock_file.");
        std::cout << "PID: " << buff << "locked file." << '\n';

        std::string str_pid(buff);
        int int_pid = std::stoi(str_pid);

        if (kill(int_pid, SIGKILL) == 0)
        {
            sleep(1);
            std::cout << "At least one process has been killed." << '\n';
            goto createfile;
        }
        else
        {
            sleep(1);
            std::cout << "Couldn't kill: " << buff << "process" << '\n';
            goto createfile;
        }

        goto loop;
    }


createfile:
    fd = create_pid_file(*argv, PID_F_PATH, 1);

    // if (flock(fd, LOCK_EX | LOCK_NB) == -1)
    // {
    //     throw std::runtime_error("File with file descriptor " + std::to_string(fd) + " is already locked by another process.");
    // }
    // std::cout << "res = " << res << '\n';

    // FILE *fp;
    // int pid = getpid();
    // char str[42];
    // itoa(pid, str, 10);
    // strcat(str, PATH);
    // printf("%s", str);
    // fp = fopen("")

    // flock(pid, );
    // fwrite();

loop:
    for (;;)
    {
        sleep(2);
    }

    return 0;
}