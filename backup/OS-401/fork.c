#include <stdio.h>
#include <unistd.h>

int main ()
{
    printf("this line wont execute");
    fork();
    for(;;)
    {
       // printf(". ");
    }
}