#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main()
{
    int fp = open("Test1.txt", O_RDONLY | O_CREAT | O_WRONLY, 0644);

    if (fp == -1)
    {
        perror("Open Fail!");
        exit(1);
    }

     

    printf("fp = %d\n", fp);

    return 0;
}