/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashigema <ashigema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 14:12:04 by ashigema          #+#    #+#             */
/*   Updated: 2023/10/21 12:44:35 by ashigema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <fcntl.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);

char	*append_buf_to_line(char *saved_line, char *buf, ssize_t bytes_read);
char	*read_until_newline(int fd, char *saved_line);
char	*extract_line_from_saved(char *saved_line);
char	*trim_saved_line(char *saved_line, size_t len);
char	*get_next_line(int fd);

#endif