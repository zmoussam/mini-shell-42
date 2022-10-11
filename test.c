#include<stdio.h>
int main()
{
    int i;
     i = 0;
    while(i <= 5)
    {
        if(i == 4)
        {
            i++;
            continue;
        }
        printf("i = %d\n", i);
        i++;
    }
}
