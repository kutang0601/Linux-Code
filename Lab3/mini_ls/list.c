#include "ls.h"

#define MAX_SIZE 1024

void list_dir(char* dirname, option* opt)
{

    FileInfor files[MAX_SIZE];
    int count;

    count = collect_files(dirname, files, MAX_SIZE, opt);

    sort_files(files, count, opt);

    print_files(dirname, files, count, opt);
}