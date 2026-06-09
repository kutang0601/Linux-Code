#include "shell.h"

int main()
{   
    init_signal();

    while (1)
    {
        Firstprint();
        
        char* order = get_order();
        if (strlen(order) == 0)
        {
            continue;
        }

        pipeST pipe;
        memset(&pipe, 0, sizeof(pipe));

        int judge = parse_line(order, &pipe);
        if (!judge)
        {
            execute(&pipe);
        }

        free_all(&pipe);
    }

    return 0;
}

