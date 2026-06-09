#include "shell.h"

static char old_path[MAX_PATHSIZE] = "";

int built(commond* com)
{
    if (com->quantity == 0)
        return 0;

    if (!(strcmp(com->oneinput[0], "exit")))
    {
        return 2;
    }

    if (!(strcmp(com->oneinput[0], "cd")))
    {
        char now_path[MAX_PATHSIZE];
        getcwd(now_path, sizeof(now_path));

        char* will_path = com->oneinput[1];

        if (will_path == NULL || !(strcmp(will_path, "~")))
        {
            will_path = getenv("HOME");
        }
        else if (!(strcmp(will_path, "-")))
        {
            if (strlen(old_path) == 0)
            {
                printf("My_shell: cd: OLDPWD 未设定");
                return 1;
            }
            will_path = old_path;
            printf("%s", old_path);
        }

        if (chdir(will_path))
        {
            perror("cd Fail!");
            return 1;
        }
        else
        {
            strcpy(old_path, now_path);
        }

        return 1;
    }   

    return 0;
}