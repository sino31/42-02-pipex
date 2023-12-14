/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shigematsuaono <shigematsuaono@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:00:27 by shigematsua       #+#    #+#             */
/*   Updated: 2023/11/24 20:10:15 by shigematsua      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*extract_path_from_env(char *envp[])
{
	size_t	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp("PATH=", envp[i], 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

static char	*find_executable_in_path(char *cmd, char *env_path)
{
	char	**path;
	char	*full_path;
	char	*tmp;
	size_t	i;

	path = ft_split(env_path, ':');
	if (!path)
		return (NULL);
	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full_path, X_OK) == 0)
		{
			free_2d_array(path);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_2d_array(path);
	return (NULL);
}

char	*get_cmd_path(char *cmd, char *envp[])
{
	char	*env_path;
	char	*cmd_path;

	env_path = extract_path_from_env(envp);
	if (!env_path)
		return (NULL);
	cmd_path = find_executable_in_path(cmd, env_path);
	if (!cmd_path)
	{
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, " :command not found\n", 21);
		exit(EXIT_FAILURE);
	}
	return (cmd_path);
}
