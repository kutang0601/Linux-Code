#include "shell.h"

void execute(pipeST* pipe_st)
{
    int count = pipe_st->com_count;

    if (count == 0)
    {
        return;
    }

    if (count == 1)
    {   
        int ret = built(&pipe_st->coms[0]);

        if (ret == 2)
        {
            free_all(pipe_st);
            exit(0);
        }
        else if (ret == 1)
            return;
    }

    int fds[MAX_COMSIZE][2];
    pid_t pids[MAX_COMSIZE];

    for (int a = 0; a < count - 1; a++)
    {
        int n1 = pipe(fds[a]);
        if (n1 < 0)
        {
            perror("pipe Fail!");
            return;
        }
    }

    for (int b = 0; b < count; b++)
    {
        pids[b] = fork();
        if (pids[b] < 0)
        {
            perror("fork Fail!");
            return;
        }

        if (pids[b] == 0)
        {
            signal(SIGINT, SIG_DFL);

            if (b == 0)
            {
                if (pipe_st->coms[b].input_file != NULL)
                {
                    int fd_in = open(pipe_st->coms[b].input_file, O_RDONLY);
                    if (fd_in < 0)
                    {
                        perror("Open Fail!");
                        exit(1);
                    }
                    dup2(fd_in, STDIN_FILENO);
                    close(fd_in);
                }       
            }
            else
            {
                dup2(fds[b - 1][0], STDIN_FILENO);
            }

            if (b == count - 1)
            {
                if (pipe_st->coms[b].output_file != NULL)
                {
                    int fd_out;
                    if (pipe_st->coms[b].input_way== 2)
                    {
                        fd_out = open(pipe_st->coms[b].output_file, O_WRONLY | O_CREAT | O_APPEND, 0664);
                    }
                    else
                    {
                        fd_out = open(pipe_st->coms[b].output_file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
                    }

                    if (fd_out < 0)
                    {
                        perror("Open Fail!");
                        exit(1);
                    }

                    dup2(fd_out, STDOUT_FILENO);
                    close(fd_out);
                }
            }
            else
            {
                dup2(fds[b][1], STDOUT_FILENO);
            }

            for (int c = 0; c < count - 1; c++)
            {
                close(fds[c][1]);
                close(fds[c][0]);
            }

            execvp(pipe_st->coms[b].oneinput[0], pipe_st->coms[b].oneinput);
            perror("exe error!");
            exit(1);
        }
    }

    for (int d = 0; d < count; d++)
    {
        for (int e = 0; e < count - 1; e++)
        {
            close(fds[e][1]);
            close(fds[e][0]);
        }
        
        if (pipe_st->backrun == 1) 
        {
            waitpid(pids[d], NULL, WNOHANG);
            printf("[Pid: %d running in background]\n", pids[d]);
        }
        else 
        {
            waitpid(pids[d], NULL, 0);
        }
    }
}