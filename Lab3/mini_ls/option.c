#include "ls.h"

void Init_OPT(option* opt)
{
    opt->Is_a = 0;
    opt->Is_l = 0;
    opt->Is_i = 0;
    opt->Is_R = 0;
    opt->Is_t = 0;
    opt->Is_S = 0;
    opt->Is_r = 0;
}

void analysis_options(int argc, char* argv[], option* opt)
{
    for (int a = 1; a < argc; a++)
    {
        if (argv[a][0] == '-')
        {
            for (int b = 1; argv[a][b] != '\0'; b++)
            {
                switch(argv[a][b])
                {
                    case 'a':
                        opt->Is_a = 1;
                        break;
                    case 'l':
                        opt->Is_l = 1;
                        break;
                    case 'i':
                        opt->Is_i = 1;
                        break;
                    case 'R':
                        opt->Is_R = 1;
                        break;
                    case 't':
                        opt->Is_t = 1;
                        break;
                    case 'S':
                        opt->Is_S = 1;
                        break;
                    case 'r':
                        opt->Is_r = 1;
                        break;
                    default:
                        break;    
                }
            }
        }
    }
}