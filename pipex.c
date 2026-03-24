/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguilber <mguilber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:52:32 by mguilber          #+#    #+#             */
/*   Updated: 2026/03/24 19:59:09 by mguilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_process_1(t_pip *u, char **a, char **e)
{
	char	**paths;

	close(u->pipe_fd[0]);
	if (u->fd_in < 0 || dup2(u->fd_in, 0) == -1)
	{
		close(u->pipe_fd[1]);
		if (u->fd_out >= 0)
			close(u->fd_out);
		if (u->fd_in >= 0)
			close(u->fd_in);
		exit(1);
	}
	if (dup2(u->pipe_fd[1], 1) == -1)
	{
		close(u->pipe_fd[1]);
		close(u->fd_in);
		close(u->fd_out);
		exit(1);
	}
	close(u->pipe_fd[1]);
	close(u->fd_in);
	close(u->fd_out);
	paths = find_path(e);
	execute_cmd(a[2], e, paths);
}

void	child_process_2(t_pip *u, char **a, char **e)
{
	char	**paths;

	close(u->pipe_fd[1]);
	if (u->fd_out < 0 || dup2(u->pipe_fd[0], 0) == -1)
	{
		close(u->pipe_fd[0]);
		if (u->fd_in >= 0)
			close(u->fd_in);
		if (u->fd_out >= 0)
			close(u->fd_out);
		exit(1);
	}
	if (dup2(u->fd_out, 1) == -1)
	{
		close(u->pipe_fd[0]);
		close(u->fd_in);
		close(u->fd_out);
		exit(1);
	}
	close(u->pipe_fd[0]);
	close(u->fd_in);
	close(u->fd_out);
	paths = find_path(e);
	execute_cmd(a[3], e, paths);
}

static void	open_files(t_pip *u, char **av)
{
	u->fd_in = open(av[1], O_RDONLY);
	if (u->fd_in < 0)
		perror(av[1]);
	u->fd_out = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (u->fd_out < 0)
		perror(av[4]);
}

void	child(t_pip u, char **av, char **env)
{
	if (u.pid1 == 0)
		child_process_1(&u, av, env);
	u.pid2 = fork();
	if (u.pid2 == 0)
		child_process_2(&u, av, env);
}

int	main(int ac, char *av[], char **env)
{
	static t_pip	u = {0};
	int				st;

	if (ac != 5)
		return (write(2, "Usage: pipex f1 cmd1 cmd2 f2\n", 29), 1);
	open_files(&u, av);
	if (pipe(u.pipe_fd) == -1)
	{
		if (u.fd_in >= 0)
			close(u.fd_in);
		if (u.fd_out >= 0)
			close(u.fd_out);
		return (1);
	}
	u.pid1 = fork();
	child(u, av, env);
	close(u.pipe_fd[0]);
	close(u.pipe_fd[1]);
	if (u.fd_in >= 0)
		close(u.fd_in);
	if (u.fd_out >= 0)
		close(u.fd_out);
	waitpid(u.pid1, NULL, 0);
	waitpid(u.pid2, &st, 0);
	return (WEXITSTATUS(st));
}
