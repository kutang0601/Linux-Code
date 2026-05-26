#include "ls.h"

void ls_basic(FileInfor files[], int count)
{
    for (int d = 0; d < count; d++)
    {
        if (d != count - 1)
        {
            printf("%s  ", files[d].name);
        }
        else
        {
            printf("%s\n", files[d].name);
        }
    }
}

void print_files(char* dirname, FileInfor files[], int count, option* opt)
{
    if (opt->Is_l)
    {
        for (int a = 0; a < count; a++)
        {
            struct passwd* pw;
            pw = getpwuid(files[a].st.st_uid);
            struct group* gr;
            gr = getgrgid(files[a].st.st_gid);
            char timechage[128];
            strftime(timechage, sizeof(timechage), "%b %d %H:%M", localtime(&files[a].st.st_mtime));
            char modechage[11];
            mode_chage(files[a].st.st_mode, modechage);
            printf("%s %ld %s %s %7ld %s %s\n", modechage, files[a].st.st_nlink, pw->pw_name, gr->gr_name, files[a].st.st_size, timechage, files[a].name);
        }
    }

    else if (opt->Is_i)
    {
        for (int b = 0; b < count; b++)
        {
            printf("%ld %s\n", files[b].st.st_ino, files[b].name);
        }
    }
    
    else if (opt->Is_R)
    {
        printf("%s:\n", dirname);
        ls_basic(files, count);
        printf("\n");
        
        for (int c = 0; c < count; c++)
        {
            if (S_ISDIR(files[c].st.st_mode))
            {
                if (judge_dad(files[c].name))
                {
                    continue;
                }
                
                list_dir(files[c].path, opt);
            }
        }
    }

    else
    {
        ls_basic(files, count);
    }
}