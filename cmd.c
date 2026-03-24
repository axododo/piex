/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mguilber <mguilber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 13:52:42 by mguilber          #+#    #+#             */
/*   Updated: 2026/03/24 13:59:28 by mguilber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_array(char **a)
{
	int	i;

	i = 0;
	while (a && a[i])
		free(a[i++]);
	free(a);
}

char	**find_path(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

char	*find_cmd(char **p, char *c)
{
	int		i;
	char	*path;

	i = 0;
	if (!c || !*c || access(c, X_OK) == 0)
		return (c);
	while (p && p[i])
	{
		path = ft_strjoin(p[i++], c);
		if (!path)
			return (NULL);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
	}
	return (NULL);
}

static void	cmd_not_found(char **args, char **paths)
{
	write(2, args[0], ft_strlen(args[0]));
	write(2, ": command not found\n", 20);
	free_array(args);
	free_array(paths);
	exit(127);
}

void	execute_cmd(char *cmd, char **env, char **paths)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (!args || !args[0])
	{
		free_array(args);
		free_array(paths);
		exit(127);
	}
	path = find_cmd(paths, args[0]);
	if (!path)
		cmd_not_found(args, paths);
	execve(path, args, env);
	if (path != args[0])
		free(path);
	free_array(args);
	free_array(paths);
	exit(126);
}
