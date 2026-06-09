#include "shell.h"

void Firstprint()
{
    char hostname[32];
    char path[MAX_PATHSIZE];

    struct passwd* pw;
    pw = getpwuid(geteuid());

    gethostname(hostname, sizeof(hostname));

    getcwd(path, sizeof(path));

    char* home = getenv("HOME");

    if (home != NULL && !(strncmp(home, path, strlen(home))))
    {
        if (!(strcmp(pw->pw_name, "root")))
        {
            printf("%s@%s:~%s# ", pw->pw_name, hostname, path + strlen(home));
        }
        else
        {
            printf("%s@%s:~%s$ ", pw->pw_name, hostname, path + strlen(home));
        }
    }
    else
    {
        if (!(strcmp(pw->pw_name, "root")))
        {
            printf("%s@%s:%s# ", pw->pw_name, hostname, path);
        }
        else
        {
            printf("%s@%s:%s$ ", pw->pw_name, hostname, path);
        }
    }
    
}

char* get_order()
{
    static char order_R[MAX_ORDERSIZE];

    if (!(fgets(order_R, sizeof(order_R), stdin)))
    {
        printf("\n");
        exit(0);
    }

    if (!order_R)
    {
        perror("Get Fail!");
        exit(1);
    }

    order_R[strcspn(order_R, "\n")] = '\0';

    return order_R;
}

void free_all(pipeST* pipe)
{
    for (int i = 0; i < MAX_COMSIZE; i++)
    {
        for (int j = 0; j < MAX_USR_INPUTSIZE; j++)
        {
            if (pipe->coms[i].oneinput[j] != NULL)
            {
                free(pipe->coms[i].oneinput[j]);
                pipe->coms[i].oneinput[j] = NULL;
            }
        }
    }

    for (int k = 0; k < MAX_COMSIZE; k++)
    {
        if (pipe->coms[k].input_file != NULL)
        {
            free(pipe->coms[k].input_file);
            pipe->coms[k].input_file = NULL;
        }
        
        if (pipe->coms[k].output_file != NULL)
        {
            free(pipe->coms[k].output_file);
            pipe->coms[k].output_file = NULL;
        }
    }

    pipe->com_count = 0;
    
}

void init_signal()
{
    signal(SIGINT, SIG_IGN);
}