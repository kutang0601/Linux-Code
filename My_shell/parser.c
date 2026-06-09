#include "shell.h"

int parse_line(char* order, pipeST* pipe)
{
    pipe->com_count = 0;
    pipe->backrun = 0; 

    int len = strlen(order) - 1;

    while (len > 0 && isspace(order[len]))
    {
        order[len] = '\0';
        len--;
    }

    if (len > 0 && order[len] == '&')
    {
        order[len] = '\0';
        pipe->backrun = 1;
    }

    char* save1;

    char* token1 = strtok_r(order, "|", &save1);

    while (token1 && pipe->com_count < MAX_COMSIZE)
    {
        if ((parse_com(token1, &(pipe->coms[pipe->com_count]))) == 0)
        {
            pipe->com_count++;
        }

        token1 = strtok_r(NULL, "|", &save1);
    }

    return (pipe->com_count > 0) ? 0 : -1;
}

int parse_com(char* com, commond* coms)
{
    coms->quantity = 0;
    coms->input_file = NULL;
    coms->output_file = NULL;
    coms->input_way = 0;

    char* temp[MAX_USR_INPUTSIZE];
    int tempsubscript = 0; 
    char* save2;

    char* token2 = strtok_r(com, " \t", &save2);
    while(token2 && tempsubscript < MAX_USR_INPUTSIZE - 1)
    {
        temp[tempsubscript] = token2;
        tempsubscript++;

        token2 = strtok_r(NULL, " \t", &save2);
    }

    for (int a = 0; a < tempsubscript; a++)
    {
        if (!strcmp(temp[a], ">"))
        {
            if (a + 1 < tempsubscript)
            {
                coms->output_file = strdup(temp[a + 1]);
                coms->input_way = 1;
                a++;
            }
        }
        else if (!strcmp(temp[a], ">>"))
        {
            if (a + 1 < tempsubscript)
            {
                coms->output_file = strdup(temp[a + 1]);
                coms->input_way = 2;
                a++;
            }
        }
        else if (!strcmp(temp[a], "<"))
        {
            if (a + 1 < tempsubscript)
            {
                coms->input_file = strdup(temp[a + 1]);
                a++;
            }
        }
        else
        {
            coms->oneinput[coms->quantity] = strdup(temp[a]);
            coms->quantity++;
        }
    }

    coms->oneinput[coms->quantity] = NULL;
    return (coms->quantity > 0) ? 0 : -1;
}