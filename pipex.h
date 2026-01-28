#ifndef PIPEX_H
# define PIPEX_h

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct s_pip {
    int fd_in;
    int fd_out;
    char *path_env;
} t_pip;

int verif(int err, char *msg);

#endif