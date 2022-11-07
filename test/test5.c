/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:04:54 by zmoussam          #+#    #+#             */
/*   Updated: 2022/09/27 21:10:00 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <signal.h>

int main(int argc, char **argv)
{
    int pid = fork();
    if (pid == -1)
        return 1;
    if (pid == 0){
        // child process 
        //kill(getpid(), SIGKILL);
       int err = execlp("ping", "ping", "-c", "1", "google.con", NULL);
       if (err == -1){
           printf("Could not find program to execute!\n");
           return 2;
       }
    } else {
        // Parent process 
        int wstatus;
        wait(&wstatus);
        if(WIFEXITED(wstatus)){
            int statusCode = WEXITSTATUS(wstatus);
            if(statusCode == 0)
                printf("Success!\n");
            else
                printf("Failure with status code %d!\n", statusCode);
        }
        printf("Some post processing goes here!\n");
    }
}