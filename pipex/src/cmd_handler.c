/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shigematsuaono <shigematsuaono@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 11:08:58 by shigematsua       #+#    #+#             */
/*   Updated: 2023/12/16 22:47:14 by shigematsua      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*extract_cmd_name(const char *str)
{
	char	*cmd_name;
	size_t	len;

	len = 0;
	while (str[len] && str[len] != ' ')
		len++;
	cmd_name = (char *)malloc(len + 1);
	if (!cmd_name)
		return (NULL);
	ft_strlcpy(cmd_name, str, len + 1);
	return (cmd_name);
}

void	run_command(char *argv, char **envp)
{
	char	*abs_path;
	char	**args;

	abs_path = get_cmd_path(extract_cmd_name(argv), envp);
	args = ft_split(argv, ' ');
	if (execve(abs_path, args, envp) == -1)
	{
		free(abs_path);
		free_2d_array(args);
		exit_with_error("execve");
	}
}

pid_t	fork_and_execute_command(int fdin, int fdout, char *cmd, char **envp)
{
	pid_t	ret;

	ret = fork();
	if (ret < 0)
		exit_with_error("fork");
	if (ret == 0)
	{
		dup2(fdin, STDIN_FILENO);
		close(fdin);
		dup2(fdout, STDOUT_FILENO);
		close(fdout);
		run_command(cmd, envp);
	}
	return (ret);
}
