#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h>

#include <sys/stat.h>

#include <unistd.h>

#include <pwd.h>

#include <grp.h>

#include <error.h>
#include <time.h>

#define MAX_FILES 1024

typedef struct FileInfor
{
    char name[MAX_FILES];
    char path[MAX_FILES];
    struct stat st;
}FileInfor;

typedef struct option
{
    int Is_a;       
    int Is_l;       
    int Is_i;       //显示 inode 编号
    int Is_R;       //递归遍历子目录
    int Is_t;       //按修改时间排序
    int Is_S;       //按文件大小排序
    int Is_r;       //反向排序
}option;

void Init_OPT(option* opt);

void analysis_options(int argc, char* argv[], option* opt);

void list_dir(char* dirname, option* opt);

int collect_files(char* dirname, FileInfor files[], int max_count, option* opt);

void sort_files(FileInfor files[], int count, option* opt);

void print_files(char* dirname, FileInfor files[], int count, option* opt);

void mode_chage(mode_t mode, char ch[]);

int judge_dad(char* name);

void ls_basic(FileInfor files[], int count);