
#include<stdio.h>
#include<unistd.h>
#include <sys/errno.h>
#include<string.h>
#include<stdlib.h>
#include <unistd.h>
#include <stdio.h>

extern char **environ;
//...
int main ()
{
int i = 0;
while(environ[i]) {
  printf("%s\n", environ[i++]); // prints in form of "variable=value"
}}