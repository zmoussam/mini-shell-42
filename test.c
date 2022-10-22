
#include<stdio.h>
#include<unistd.h>
#include <sys/errno.h>
#include<string.h>
#include<stdlib.h>
int main()
{
    printf("tty = %s\n", ttyname(1));
}