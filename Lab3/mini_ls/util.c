#include "ls.h"

void mode_chage(mode_t mode, char ch[])
{
    ch[0] = S_ISDIR(mode) ? 'd' : '-';
    
    ch[1] = (mode & S_IRUSR) ? 'r' : '-';
    ch[2] = (mode & S_IWUSR) ? 'w' : '-';
    ch[3] = (mode & S_IXUSR) ? 'x' : '-';

    ch[4] = (mode & S_IRGRP) ? 'r' : '-';
    ch[5] = (mode & S_IWGRP) ? 'w' : '-';
    ch[6] = (mode & S_IXGRP) ? 'x' : '-';

    ch[7] = (mode & S_IROTH) ? 'r' : '-';
    ch[8] = (mode & S_IWOTH) ? 'w' : '-';
    ch[9] = (mode & S_IXOTH) ? 'x' : '-';

    ch[10] = '\0';
} 

int judge_dad(char* name)
{
    return !strcmp(name, ".") || !strcmp(name, ".."); 
}