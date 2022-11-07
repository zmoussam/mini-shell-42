#include <unistd.h>
int main()
{
    char *argv[] = {"/bin/ls","-la" ,NULL};
    if(!access("/bin/ls", X_OK))
    {
        execve("/bin/ls",argv ,NULL);
    }
}