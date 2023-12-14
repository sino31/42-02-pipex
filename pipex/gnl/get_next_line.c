/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shigematsuaono <shigematsuaono@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 19:20:05 by ashigema          #+#    #+#             */
/*   Updated: 2023/12/01 11:27:35 by shigematsua      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*append_buf_to_line(char *saved_line, char *buf, ssize_t bytes_read)
{
	char	*tmp;

	if (bytes_read <= 0)
	{
		if (saved_line && *saved_line)
		{
			tmp = ft_strdup(saved_line);
			free(saved_line);
			if (!tmp)
				return (NULL);
			return (tmp);
		}
		free(saved_line);
		return (NULL);
	}
	buf[bytes_read] = '\0';
	tmp = ft_strjoin(saved_line, buf);
	free(saved_line);
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*read_until_newline(int fd, char *saved_line)
{
	ssize_t	bytes_read;
	char	*buf;

	buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
	{
		free(saved_line);
		return (NULL);
	}
	while (!ft_strchr(saved_line, '\n'))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		saved_line = append_buf_to_line(saved_line, buf, bytes_read);
		if (!saved_line || bytes_read == 0)
		{
			free(buf);
			if (bytes_read == 0)
				return (saved_line);
			return (NULL);
		}
	}
	free(buf);
	return (saved_line);
}

char	*extract_line_from_saved(char *saved_line)
{
	size_t	i;
	char	*line;

	i = 0;
	while (saved_line[i] && saved_line[i] != '\n')
		i++;
	line = (char *)malloc((i + 2) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (saved_line[i] && saved_line[i] != '\n')
	{
		line[i] = saved_line[i];
		i++;
	}
	if (saved_line[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*trim_saved_line(char *saved_line, size_t len)
{
	char	*new_saved_line;
	size_t	i;

	if (!saved_line[len - 1])
	{
		free(saved_line);
		return (NULL);
	}
	new_saved_line = (char *)malloc(ft_strlen(saved_line) - len + 1);
	if (!new_saved_line)
	{
		free(saved_line);
		return (NULL);
	}
	i = 0;
	while (saved_line[len])
		new_saved_line[i++] = saved_line[len++];
	new_saved_line[i] = '\0';
	free(saved_line);
	return (new_saved_line);
}

char	*get_next_line(int fd)
{
	static char	*saved_line;
	char		*line;

	saved_line = NULL;
	if (fd > OPEN_MAX - 1 || fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!saved_line)
	{
		saved_line = ft_strdup("");
		if (!saved_line)
			return (NULL);
	}
	saved_line = read_until_newline(fd, saved_line);
	if (!saved_line)
		return (NULL);
	line = extract_line_from_saved(saved_line);
	if (!line)
		return (NULL);
	saved_line = trim_saved_line(saved_line, ft_strlen(line));
	if (!saved_line)
		return (NULL);
	return (line);
}
