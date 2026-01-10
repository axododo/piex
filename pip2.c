#include "pipex.h"
#include <stdio.h>

char **pars_cmd(char *cmd) {
  char **pcmd = ft_split(cmd, ' ');
  return(pcmd);
}

char *find_path(char **envp)  {
  int i = 0;
  int valid = -1;
  while (envp[i]) {
    valid = ft_strncmp(envp[i], "PATH=", 5);
    if (valid == 0) return (envp[i] + 5);
    i++;
  }
  return (NULL);
}

char *find_cmd(char **path, char *cmd) {
  int i = 0;
  while (path[i]) {
    char *gpath = ft_strjoin(path[i], cmd);
    if ((access(gpath, X_OK)) == 0) {
      printf("chemin pr la commande trouver -> %s\n", gpath);
      return (gpath);
    }
    i++;
  }
  return (NULL);
}

int main(int argc, char *argv[], char **envp) {
  int pipe_fd[2];
  if (argc != 5) {
    write(1, "doit contenir 5 cmd -> f1 cmd1 cmd2 f2", 38);
    return(1);
  }
  int fd_in = open(argv[1], O_RDONLY);
  //printf("%i\n", fd_in);
  if (fd_in == -1) {
    perror("entree non valable");
    close(fd_in);
    //printf("%i\n", fd_in);
    exit(1);
  }
  int fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
  char *path_env = find_path(envp);
  char **path = ft_split(path_env, ':');
  int i = 0;
  /*while (path[i]) {
    printf("%s\n", path[i]);
    i++;
  }*/

  char *cmd1 = argv[2];
  char **pcmd1 = pars_cmd(cmd1);
  char *cmd_path = find_cmd(path, pcmd1[0]);

  int a = pipe(pipe_fd);
  printf("%i\n", a);

  int pid1 = fork();
  //int pid2 = fork();

  if (pid1 == 0) {
    printf("\n enffant n1 \n");
    
  }
  // if (pid2 == 0) {
  //   printf("\n enffant n2 \n");
  //   execv(pcmd1[1], NULL);
  // }
  int stat;
  waitpid(pid1, &stat, 0);

  return 0;
}
