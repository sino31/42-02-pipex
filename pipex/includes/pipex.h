/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashigema <ashigema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:16:42 by ashigema          #+#    #+#             */
/*   Updated: 2023/12/13 20:31:04 by ashigema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../gnl/get_next_line.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// libft-utils/
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char *str, char delim);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);

// pipex_utils.c
void	free_2d_array(char **array);
void	exit_with_error(char *err);

// get_cmd_path.c
char	*get_cmd_path(char *cmd, char *envp[]);

// cmd_handler.c
pid_t	fork_and_execute_command(int fdin, int fdout, char *cmd, char **envp);

// heredoc.c
int		here_doc(char *argv[]);

// main.c
int		main(int argc, char *argv[], char *envp[]);

#endif