#include "pipex.h"


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
}

int main(int argc, char *argv[], char **envp) {
  if (argc != 5) {
    write(1, "doit contenir 5 cmd -> f1 cmd1 cmd2 f2", 38);
    return(1);
  }
  int fd_int = open(argv[1], O_RDONLY);
  int fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
  char *path_env = find_path(envp);
  char **path = ft_split(path_env, ':');
  int i = 0;
  while (path[i]) {
    printf("%s\n", path[i]);
    i++;
  }
  char *cmd1 = argv[2];
  find_cmd(path, cmd1);
  return 0;
}
