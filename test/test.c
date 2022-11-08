#include <fcntl.h>
int main()
{
    int fd;
    while(1)
    {
        fd = open("fd", O_CREAT, 0777);
    }
}