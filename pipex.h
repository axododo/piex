#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct s_pip
{
	int		fd_in;
	int		fd_out;
	int		pipe_fd[2];
	char	**paths;
	pid_t	pid1;
	pid_t	pid2;
}	t_pip;

char	**find_path(char **envp);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	free_array(char **arr);
void	error_exit(char *msg);
void	execute_cmd(char *cmd, char **envp, char **paths);

#endif
