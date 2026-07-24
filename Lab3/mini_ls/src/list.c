#include "ls.h"

void list_dir(char* dirname, option* opt)
{

    FileInfor *files = malloc(sizeof(FileInfor) * MAX_SIZE);

    if (files == NULL)
    {
        perror("Malloc Fail!");
        exit(1);
    }
    int count;

    count = collect_files(dirname, files, MAX_SIZE, opt);

    if (count <= 0)
    {
        free(files);
        return;
    }

    sort_files(files, count, opt);

    print_files(dirname, files, count, opt);

    free(files);
}