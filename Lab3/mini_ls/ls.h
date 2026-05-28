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

#define MAX_SIZE 100000
#define MAX_PATH 100000

typedef struct FileInfor
{
    char name[256];
    char path[MAX_PATH];
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
    int Is_s;       //显示文件占用的磁盘块
}option;

void Init_OPT(option* opt);

int analysis_options(char dirname[][1024],  int argc, char* argv[], option* opt);

void list_dir(char* dirname, option* opt);

int collect_files(char* dirname, FileInfor files[], int max_count, option* opt);

void sort_files(FileInfor files[], int count, option* opt);

void print_files(char* dirname, FileInfor files[], int count, option* opt);

void mode_chage(mode_t mode, char ch[]);

int judge_dad(char* name);

void ls_basic(FileInfor files[], int count);