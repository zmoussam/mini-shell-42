#include<stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <fcntl.h>
int main()
{
    int fd;
    fd = open("/etc/passwd", O_RDWR, 0777);
    printf("fd = %d\n", fd);

}
