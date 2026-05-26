#include "ls.h"

void sort_files(FileInfor files[], int count, option* opt)
{
    if (opt->Is_t)
    {
        for (int a = 0; a < count - 1; a++)
        {
            for (int b = 0; b < count - a - 1; b++)
            {
                if (files[b].st.st_mtime < files[b + 1].st.st_mtime)
                {
                    FileInfor tmp = files[b];
                    files[b] = files[b + 1];
                    files[b + 1] = tmp;
                }
            }
        }
    }
    
    if (opt->Is_S)
    {
        for (int c = 0; c < count - 1; c++)
        {
            for (int d = 0; d < count - c - 1; d++)
            {
                if (files[d].st.st_size < files[d + 1].st.st_size)
                {
                    FileInfor tmp = files[d];
                    files[d] = files[d + 1];
                    files[d + 1] = tmp;
                }
            }
        }
    }

    if (opt->Is_r)
    {
        int head = 0;
        int tail = count - 1;
        
        while (head < tail)
        {
            FileInfor tmp = files[head];
            files[head] = files[tail];
            files[tail] = tmp;
            head++;
            tail--;    
        }        
    }

}