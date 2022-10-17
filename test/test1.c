/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 21:56:37 by zmoussam          #+#    #+#             */
/*   Updated: 2022/09/25 22:14:02 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<time.h>

int main(int argc, char **argv)
{
    int p1[2];
    if (pipe(p1) == -1){ return 1;}
    int pid = fork();
    if (pid == -1) { return 2;}
    if (pid == 0) {
        // child process
        int x;
        if (read(p1[0], &x, sizeof(x)) == -1) {return 3;}
        printf("Received %d\n", x);
        x *= 4;
        if (write(p1[1], &x, sizeof(x)) == -1) { return 4;}
        printf("Wrote %d\n", x);
    } else {
        // parent precess
        srand(time(NULL));
        int y = rand() % 10;
        if (write(p1[1], &y, sizeof(y)) == -1) { return 5;}
        printf("Wrote %d\n", y);
        if (read(p1[0], &y, sizeof(y)) == -1) { return 6;}
        printf("Result is %d\n", y);
        wait(NULL);
    }
    close(p1[0]);
    close(p1[1]);
    return 0;
}