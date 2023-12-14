/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shigematsuaono <shigematsuaono@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:15:07 by ashigema          #+#    #+#             */
/*   Updated: 2023/12/14 11:07:32 by shigematsua      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static int	initialize(int argc, char *argv[], int inout_fds[2], pid_t **ret)
{
	if (argc < 4)
	{
		errno = EINVAL;
		exit_with_error("argc");
	}
	*ret = (pid_t *)malloc((argc - 1) * sizeof(pid_t));
	if (!*ret)
		exit_with_error("malloc");
	if (ft_strcmp(argv[1], "here_doc") == 0)
	{
		inout_fds[0] = here_doc(argv);
		inout_fds[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND,
				0644);
	}
	else
	{
		inout_fds[0] = open(argv[1], O_RDONLY);
		inout_fds[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (inout_fds[0] < 0 || inout_fds[1] < 0)
		exit_with_error("file");
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		return (4);
	return (3);
}

static void	wait_for_child_processes(void)
{
	int		status;
	pid_t	wpid;

	wpid = 1;
	while (wpid > 0)
	{
		wpid = waitpid(-1, &status, WNOHANG);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			exit_with_error("child_process");
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int		i;
	int		j;
	pid_t	*ret;
	int		pipe_fd[2];
	int		inout_fds[2];

	i = initialize(argc, argv, inout_fds, &ret);
	j = 0;
	while (i < argc - 2)
	{
		close(pipe_fd[0]);
		if (pipe(pipe_fd) < 0)
			exit_with_error("pipe");
		ret[j] = fork_and_execute_command(inout_fds[0], pipe_fd[1], argv[i],
				envp);
		inout_fds[0] = pipe_fd[0];
		close(pipe_fd[1]);
		j++;
		i++;
	}
	ret[j] = fork_and_execute_command(inout_fds[0], inout_fds[1], argv[i],
			envp);
	wait_for_child_processes();
	close(inout_fds[0]);
	close(inout_fds[1]);
	free(ret);
}

// __attribute__((destructor)) static void destructor()
// {
// 	system("leaks -q pipex");
// }