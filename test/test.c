#include<stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
 #include <fcntl.h>
int main()
{
    static char *str;
    char    *copy;
    str = getcwd(NULL, 0);
    copy = str;
    str = copy;
    free(copy);


}
