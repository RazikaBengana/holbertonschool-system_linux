#ifndef MAIN_H
#define MAIN_H


#ifndef PATH_MAX
#define PATH_MAX 4096
#endif


#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <limits.h>
#include <stddef.h>
#include <pwd.h>
#include <grp.h>


/**
 * struct Options - structure that stores flags for directory listing options,
 * mirroring common options found in the Unix 'ls' command
 *
 * @op_a: Flag to include hidden files in the listings ('-a' option in ls)
 * @op_l: Flag to use a long listing format ('-l' option in ls)
 * @op_1: Flag to ensure each entry is output on a separate line ('-1' option in ls)
 * @op_A: Flag to list all entries except for '.' and '..' ('-l' option with ls)
 */

struct Options {
    int op_a;
    int op_l;
    int op_1;
    int op_A;
};


void list_directory(const char *program_name, const char *dir, struct Options opts);
void permissions(struct stat file_stat);
size_t my_strlen(const char *str);
int my_strcmp(const char *str1, const char *str2);
char *my_strncpy(char *dest, const char *src, size_t n);



#endif /* MAIN_H */
