#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <limits.h>
#include <ctype.h>
#include <signal.h>
#include <fcntl.h>
#include <error.h>
#include <pwd.h>

#define MAX_USR_INPUTSIZE 128
#define MAX_COMSIZE 16
#define MAX_PATHSIZE 256
#define MAX_ORDERSIZE 128

//单个命令结构体定义
typedef struct commond
{
    char* oneinput[MAX_USR_INPUTSIZE];
    int quantity;
    
    char* input_file;
    char* output_file;

    int input_way;
}commond;

//管道符号相关结构定义
typedef struct pipeST
{
    commond coms[MAX_COMSIZE];
    
    int com_count;

    int backrun;
}pipeST;

void Firstprint();

char* get_order();

int parse_line(char* order, pipeST* pipe);

int parse_com(char* com, commond* coms);

void execute(pipeST* pipe);

int built(commond* com);

void free_all(pipeST* pipe);

void init_signal();