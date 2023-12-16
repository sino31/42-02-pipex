/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shigematsuaono <shigematsuaono@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:16:42 by ashigema          #+#    #+#             */
/*   Updated: 2023/12/16 22:48:05 by shigematsua      ###   ########.fr       */
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
char	*extract_path_from_env(char *envp[]);
char	*find_executable_in_path(char *cmd, char *env_path);
char	*get_cmd_path(char *cmd, char *envp[]);

// cmd_handler.c
char	*extract_cmd_name(const char *str);
void	run_command(char *argv, char **envp);
pid_t	fork_and_execute_command(int fdin, int fdout, char *cmd, char **envp);

// heredoc.c
char	*process_stdin(char *argv[], char *line, char *tmp);
int		here_doc(char *argv[]);

// main.c
int	initialize(int argc, char *argv[], int inout_fds[2], pid_t **ret);
void	wait_for_child_processes(void);
int		main(int argc, char *argv[], char *envp[]);

#endif