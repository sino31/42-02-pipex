/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shigematsuaono <shigematsuaono@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:53:36 by ashigema          #+#    #+#             */
/*   Updated: 2023/11/24 20:07:02 by shigematsua      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	here_doc(char *argv[])
{
	char *line;
	int fd[2];

	line = NULL;
	if (pipe(fd) != 0)
		exit_with_error("pipe");
	while (1)
	{
		write(STDOUT_FILENO, ">", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
		line = NULL;
	}
	close(fd[1]);
	return (fd[0]);
}