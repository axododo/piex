#include "pipex.h"


ft_verif( int argc, char *argv[], char **envp) {


}



int main( int argc, char **argv[], char **envp) {
    if(argc != 5) {
        write(2, "BAD NB ARG", 11);
        return;
    }

    // Ouverture fichiers
    int fd_in = open(argv[1], O_RDONLY);
    if (fd_in == -1) {
        perror("input file");
        exit(1);
    }
    
    int fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd_out == -1) {
        perror("output file");
        close(fd_in);
        exit(1);
    }
}