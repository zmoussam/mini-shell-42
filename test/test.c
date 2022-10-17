/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 16:48:41 by zmoussam          #+#    #+#             */
/*   Updated: 2022/10/03 00:02:21 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/shell.h"
#include <unistd.h>
#include<stdio.h>
#include <stdlib.h>
int main(int arc, char **arv)
{
    if(chdir("-") == -1)
        system("pwd");
    // int fd[2];
    // if (pipe(fd) == -1){
    //     printf("An error ocurred with opening the pipe\n");
    //     return 1;
    // }
    // int id = fork();
    // if(id == -1){
    //     printf("An error ocurred with fork\n");
    //     return 4;
    // }
    // if(id == 0){
    //     close(fd[0]);
    //     char x[10];
    //     printf("Input a number: ");
    //     scanf("%s", x);
    //     write(fd[1], x, sizeof(char) * 10);
    //     close(fd[1]);
    // }
    // else {
    //     close(fd[1]);
    //     char y[10];
    //     read(fd[0], y, sizeof(char) * 10);
    //     close(fd[0]);
    //     printf("Got from child process %s\n", y);
    // }
    // return 0;
}