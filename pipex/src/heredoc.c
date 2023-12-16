/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shigematsuaono <shigematsuaono@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:53:36 by ashigema          #+#    #+#             */
/*   Updated: 2023/12/16 22:42:07 by shigematsua      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

char	*process_stdin(char *argv[], char *line, char *tmp)
{
	write(STDOUT_FILENO, ">", 1);
	line = get_next_line(STDIN_FILENO);
	if (!line)
		return (NULL);
	tmp = ft_strdup(line);
	if (!tmp)
	{
		free(line);
		return (NULL);
	}
	tmp[ft_strlen(tmp) - 1] = '\0';
	if (ft_strcmp(tmp, argv[2]) == 0)
	{
		free(line);
		free(tmp);
		return (NULL);
	}
	free(tmp);
	return (line);
}

int	here_doc(char *argv[])
{
	char	*line;
	char	*tmp;
	int		fd[2];

	line = NULL;
	tmp = NULL;
	if (pipe(fd) != 0)
		exit_with_error("pipe");
	while (1)
	{
		line = process_stdin(argv, line, tmp);
		if (!line)
			break ;
		write(fd[1], line, ft_strlen(line));
		free(line);
		free(tmp);
		line = NULL;
	}
	close(fd[1]);
	return (fd[0]);
}
