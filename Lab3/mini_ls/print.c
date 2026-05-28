#include "ls.h"

void ls_print(FileInfor files[], int count, option* opt)
{
    if (opt->Is_l)
    {
        for (int a = 0; a < count; a++)
        {
            struct passwd* pw;
            pw = getpwuid(files[a].st.st_uid);
    
            struct group* gr;
            gr = getgrgid(files[a].st.st_gid);
    
            char pw_name_str[32];
            char gr_name_str[32];
    
            if (pw != NULL) 
            {
                strncpy(pw_name_str, pw->pw_name, sizeof(pw_name_str) - 1);
            } 
            else 
            {
                snprintf(pw_name_str, sizeof(pw_name_str), "%d", files[a].st.st_uid);
            }
    
            if (gr != NULL) 
            {
                strncpy(gr_name_str, gr->gr_name, sizeof(gr_name_str) - 1);
            } 
            else 
            {
                snprintf(gr_name_str, sizeof(gr_name_str), "%d", files[a].st.st_gid);
            }

            char timechage[128];
            strftime(timechage, sizeof(timechage), "%b %d %H:%M", localtime(&files[a].st.st_mtime));
    
            char modechage[11];
            mode_chage(files[a].st.st_mode, modechage);
    
            printf("%s %5ld %s %s %7ld %s %s\n", modechage, files[a].st.st_nlink, pw_name_str, gr_name_str, files[a].st.st_size, timechage, files[a].name);
        }
    }

    else if (opt->Is_i)
    {
        for (int b = 0; b < count; b++)
        {
            printf("%8ld %s\n", files[b].st.st_ino, files[b].name);
        }
    }

    else if (opt->Is_s)
    {
        for (int e = 0; e < count; e++)
        {
            printf("%-4ld%s\n", files[e].st.st_blocks / 2, files[e].name);
        }
    }

    else
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
}

void print_files(char* dirname, FileInfor files[], int count, option* opt)
{   
    if (opt->Is_R)
    {
        printf("\n%s:\n", dirname);
        ls_print(files, count, opt);
        
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
        ls_print(files, count, opt);
    }
}