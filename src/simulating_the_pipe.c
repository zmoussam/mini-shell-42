/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulating_the_pipe.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 06:57:19 by zmoussam          #+#    #+#             */
/*   Updated: 2022/09/28 08:16:32 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char **argv)
{
    int fd[2];
    if (pipe(fd) == -1){
        return 1;
    }
    int pid = fork();
    if (pid == 0){
        // child process 1 (ping)
        dup2(fd[1], STDOUT_FILENO);
        execlp("ping", "ping", "-c", "5", "google.com", NULL);
    }
    else {
        // parent process
        waitpid(pid, NULL, 0);
        int fd2[2];
        if (pipe(fd2) == -1)
            return 1;
        int pid2 = fork();
        if (pid2 == 0)
        {
            dup2(fd[0], STDIN_FILENO);
            dup2(fd2[1], STDOUT_FILENO);
            close(fd[0]);
            close(fd[1]);
            execlp("grep", "grep", "ttl", NULL);
            
        }
        else{
            dup2(fd2[0], STDIN_FILENO);
            close(fd[0]);
            close(fd[1]);
            close(fd2[0]);
            close(fd2[1]);
            execlp("wc", "wc" , "-l", NULL);
        }
     }
}
