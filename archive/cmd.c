#include "pipex.h"


char **pars_cmd(char *cmd) {
    char **pcmd = ft_split(cmd, ' ');
    return (pcmd);
}

char *find_path(char **envp) {
    int i = 0;
    while (envp[i]) {
        if (ft_strncmp(envp[i], "PATH=", 5) == 0)
            return (envp[i] + 5);
        i++;
    }
    return (NULL);
}

char *find_cmd(char **path, char *cmd) {
    int i = 0;
    while (path[i]) {
        char *gpath = ft_strjoin(path[i], cmd);
        if (access(gpath, X_OK) == 0)
            return (gpath);
        free(gpath);
        i++;
    }
    return (NULL);
}

void free_array(char **arr) {
    int i = 0;
    while (arr[i]) {
        free(arr[i]);
        i++;
    }
    free(arr);
}