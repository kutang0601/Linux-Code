#include "ls.h"

int collect_files(char* dirname, FileInfor files[], int max_count, option* opt)
{
    DIR* dir = opendir(dirname);
    
    if (dir == NULL)
    {
        perror("Open Fail!");
        return -1;
    }

    int count = 0;
    struct dirent* entry;

    while ((entry = readdir(dir)) != NULL)
    {
        if (!(opt->Is_a) && (entry->d_name[0]) == '.')
        {
            continue;
        }

        strcpy(files[count].name, entry->d_name);

        snprintf(files[count].path, MAX_PATH, "%s/%s", dirname, entry->d_name);

        if (lstat(files[count].path, &files[count].st) == -1)
        {
            continue;
        }

        count++;

        if (count >= max_count)
            break;
    }

    closedir(dir);

    return count;

}