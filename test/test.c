#include <fcntl.h>
#include<string.h>
#include<errno.h>
#include<stdio.h>
#include <unistd.h>
int main()
{
    int pid;

   printf("tty = %d\n", isatty(1));
}