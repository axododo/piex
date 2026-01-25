#include "pipex.h"
#include <stdio.h>


void child_process(int fd_in, int fd_out, int pipe_fd[2],
                   char **path, char **pcmd, char *cmd_path, char **envp, int cmd_num) {
    dup2(fd_in, STDIN_FILENO);

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    close(fd_in);
    close(fd_out);

    free_array(path);
    free_array(pcmd);
    printf("%s\n", cmd_path);
    execve(cmd_path, pcmd, envp);

    exit(127);
}

int main(int argc, char *argv[], char **envp) {
    int pipe_fd[2];

  
    if (argc != 5) {
        write(2, "BAD NB ARG", 11);
        return (1);
    }

   
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

   
    char *path_env = find_path(envp);
    if (!path_env) {
        write(2, "PATH not found\n", 15);
        close(fd_in);
        close(fd_out);
        exit(1);
    }

    char **path = ft_split(path_env, ':');
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        free_array(path);
        close(fd_in);
        close(fd_out);
        exit(1);
    }

    char **pcmd1 = pars_cmd(argv[2]);
    char *cmd1_path = find_cmd(path, pcmd1[0]);
    if (!cmd1_path) {
        write(2, "command not found: ", 19);
        write(2, pcmd1[0], ft_strlen(pcmd1[0]));
        write(2, "\n", 1);
        free_array(path);
        free_array(pcmd1);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        close(fd_in);
        close(fd_out);
        exit(127);
    }

    int pid1 = fork();
    if (pid1 == -1) {
        perror("fork");
        free_array(path);
        free_array(pcmd1);
        free(cmd1_path);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        close(fd_in);
        close(fd_out);
        exit(1);
    }

    if (pid1 == 0)
        printf("%s", cmd_path);
        child_process(fd_in, fd_out, pipe_fd, path, pcmd1, cmd1_path, envp, 1);

    char **pcmd2 = pars_cmd(argv[3]);
    char *cmd2_path = find_cmd(path, pcmd2[0]);
    if (!cmd2_path) {
        write(2, "command not found: ", 19);
        write(2, pcmd2[0], ft_strlen(pcmd2[0]));
        write(2, "\n", 1);
        free_array(pcmd2);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        close(fd_in);
        close(fd_out);
        waitpid(pid1, NULL, 0);
        exit(127);
    }

    int pid2 = fork();
    if (pid2 == -1) {
        perror("fork");
        free_array(pcmd2);
        free(cmd2_path);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        close(fd_in);
        close(fd_out);
        waitpid(pid1, NULL, 0);
        exit(1);
    }

    if (pid2 == 0)
        child_process(fd_in, fd_out, pipe_fd, path, pcmd2, cmd2_path, envp, 2);

    close(pipe_fd[0]);
    close(pipe_fd[1]);
    close(fd_in);
    close(fd_out);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return (0);
}
