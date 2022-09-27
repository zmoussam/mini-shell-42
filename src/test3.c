#include<unistd.h>
#include<stdio.h>
int main(int ac, char **av)
{
    while(1337)
        execve("/bin/ls", av, NULL);
    printf("hi\n");
}