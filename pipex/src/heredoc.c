/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashigema <ashigema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 12:53:36 by ashigema          #+#    #+#             */
/*   Updated: 2023/12/15 18:14:38 by ashigema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	here_doc(char *argv[])
{
	char	*line;
	char	*tmp;
	int		fd[2];

	line = NULL;
	if (pipe(fd) != 0)
		exit_with_error("pipe");
	while (1)
	{
		write(STDOUT_FILENO, ">", 1);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break ;
		tmp = ft_strdup(line);
		if (!tmp)
		{
			free(line);
			break ;
		}
		tmp[ft_strlen(tmp) - 1] = '\0';
		if (ft_strcmp(tmp, argv[2]) == 0)
		{
			free(line);
			free(tmp);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
		free(tmp);
		line = NULL;
	}
	close(fd[1]);
	return (fd[0]);
}
 