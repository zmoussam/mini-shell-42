#include<stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <fcntl.h>
 #include <string.h>
int main(int argc, char **argv)
{
    printf("HOME = %d\n", sizeof(argv[1]));
}
