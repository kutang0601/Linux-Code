#include "ls.h"

int main(int argc, char* argv[])
{
    option opt;
    char dirname[100][1024] = {"."};
    Init_OPT(&opt);
    int judge = analysis_options(dirname, argc, argv, &opt);
    if (!judge)
    {
        list_dir(dirname[0], &opt);
    }
    else
    {
        for (int a = 0; a < judge; a++)
        {
            printf("%s:\n", dirname[a]);
            list_dir(dirname[a], &opt);
        }
    }
    return 0;
}