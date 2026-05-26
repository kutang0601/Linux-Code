#include "ls.h"

int main(int argc, char* argv[])
{
    option opt;
    Init_OPT(&opt);
    analysis_options(argc, argv, &opt);
    list_dir(".", &opt);
    return 0;
}