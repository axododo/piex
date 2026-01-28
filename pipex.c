
#include "pipex.h"
#include <stdio.h>

int verif(int err, char *msg) {
    if (err == -1){
        perror("input file");
        exit(1);
    }
}


int main( int argc, char *argv[], char **envp) {
    t_pip util;

    if (argc != 5) {
        write(2, "bad nb arg", 11);
        return(1);
    }
    util.fd_in = open(argv[1], O_RDONLY);
    util.fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    verif(fd_in, "input file");
    verif(fd_out, "output file");
}