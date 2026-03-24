/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguilber <mguilber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:52:50 by mguilber          #+#    #+#             */
/*   Updated: 2026/03/24 13:52:50 by mguilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>

typedef struct s_pip
{
	int		fd_in;
	int		fd_out;
	int		pipe_fd[2];
	pid_t	pid1;
	pid_t	pid2;
}	t_pip;

char	**find_path(char **envp);
int		ft_strncmp(const char *s1, const char *s2, unsigned int n);
char	**ft_split(char const *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
char	*ft_substr(const char *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(const char *s1, const char *s2);
void	free_array(char **arr);
void	error_exit(char *msg);
void	execute_cmd(char *cmd, char **envp, char **paths);

#endif
