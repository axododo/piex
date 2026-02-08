#include "pipex.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*find_cmd(char **paths, char *cmd)
{
	int		i;
	char	*full_path;

	i = 0;
	if (!paths || !cmd)
		return (NULL);
	if (access(cmd, F_OK | X_OK) == 0)
		return (cmd);
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], cmd);
		if (access(full_path, F_OK | X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	return (NULL);
}

void	execute_cmd(char *cmd, char **envp, char **paths)
{
	char	**cmd_args;
	char	*cmd_path;

	cmd_args = ft_split(cmd, ' ');
	if (!cmd_args || !cmd_args[0])
	{
		write(2, "Error: command not found\n", 25);
		exit(127);
	}
	cmd_path = find_cmd(paths, cmd_args[0]);
	if (!cmd_path)
	{
		write(2, "Error: command not found: ", 26);
		write(2, cmd_args[0], ft_strlen(cmd_args[0]));
		write(2, "\n", 1);
		free_array(cmd_args);
		exit(127);
	}
	if (execve(cmd_path, cmd_args, envp) == -1)
	{
		perror("execve");
		free_array(cmd_args);
		exit(126);
	}
}
