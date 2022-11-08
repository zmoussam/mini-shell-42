#include<unistd.h>
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
int main(int ac, char **av)
{
    int pid = fork();
    if (pid == -1)
        return (1);
    if (pid == 0){
        // child process 
        int file = open("pingResults.txt", O_WRONLY | O_CREAT, 0777);
        if (file == -1){
            return 2;
        }
        printf("the fd to pingResult %d\n", file);
        int file2 = dup2(file, STDOUT_FILENO);
        printf("The dublicated fd : %d\n", file2);
        close(file);
        int err = execlp("ping", "ping", "-c", "1", "google.com", NULL);
        if (err == -1){
            printf("Could not find programm to execute!\n");
            return 2;
        }
    }
    else {
        int wstatus;
        // Parent process
        wait(&wstatus);
        if (WIFEXITED(wstatus)){
            int statusCode = WEXITSTATUS(wstatus);
            if (statusCode == 0){
                printf("Success!\n");
            } else {
                printf("Failure with status code %d\n", statusCode);
            }
        }
    }

}
