#include "pipex.h"

void	error_exit(char *msg)
{
	perror(msg);
	exit(1);
}

char	**find_path(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

void	child_process_1(t_pip *util, char **argv, char **envp)
{
	close(util->pipe_fd[0]);
	dup2(util->fd_in, STDIN_FILENO);
	dup2(util->pipe_fd[1], STDOUT_FILENO);
	close(util->pipe_fd[1]);
	close(util->fd_in);
	execute_cmd(argv[2], envp, util->paths);
}

void	child_process_2(t_pip *util, char **argv, char **envp)
{
	close(util->pipe_fd[1]);
	dup2(util->pipe_fd[0], STDIN_FILENO);
	dup2(util->fd_out, STDOUT_FILENO);
	close(util->pipe_fd[0]);
	close(util->fd_out);
	execute_cmd(argv[3], envp, util->paths);
}

int	main(int argc, char *argv[], char **envp)
{
	t_pip	util;

	if (argc != 5)
	{
		write(2, "Usage: ./pipex file1 cmd1 cmd2 file2\n", 38);
		return (1);
	}
	util.fd_in = open(argv[1], O_RDONLY);
	util.fd_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (util.fd_in == -1)
		error_exit("input file");
	if (util.fd_out == -1)
		error_exit("output file");
	util.paths = find_path(envp);
	if (pipe(util.pipe_fd) == -1)
		error_exit("pipe");
	util.pid1 = fork();
	if (util.pid1 == -1)
		error_exit("fork");
	if (util.pid1 == 0)
		child_process_1(&util, argv, envp);
	util.pid2 = fork();
	if (util.pid2 == -1)
		error_exit("fork");
	if (util.pid2 == 0)
		child_process_2(&util, argv, envp);
	close(util.pipe_fd[0]);
	close(util.pipe_fd[1]);
	close(util.fd_in);
	close(util.fd_out);
	waitpid(util.pid1, NULL, 0);
	waitpid(util.pid2, NULL, 0);
	free_array(util.paths);
	return (0);
}
