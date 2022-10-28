#include<stdio.h>
 #include <stdlib.h>
 #include <unistd.h>
int main()
{
    static char *pwd;

    pwd = getcwd(NULL, 0);
    printf("home = %s\n", pwd);
    free(pwd); 
}