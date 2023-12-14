/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashigema <ashigema@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 14:36:15 by ashigema          #+#    #+#             */
/*   Updated: 2023/10/27 19:31:52 by ashigema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static size_t	count_str(char *str, char delim)
{
	size_t	i;
	size_t	cnt;

	i = 0;
	cnt = 0;
	while (str[i])
	{
		while (str[i] && str[i] == delim)
			i++;
		if (str[i])
		{
			cnt++;
			while (str[i] && str[i] != delim)
				i++;
		}
	}
	return (cnt);
}

static void	*free_result(char **result, size_t i)
{
	while (i >= 0)
		free(result[i--]);
	free(result);
	return (NULL);
}

char	**ft_split(char *str, char delim)
{
	char	**result;
	size_t	i;
	size_t	j;
	size_t	str_i;
	size_t	str_cnt;

	str_cnt = count_str(str, delim);
	result = malloc((str_cnt + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	str_i = 0;
	while (i < str_cnt)
	{
		while (str[str_i] == delim)
			str_i++;
		j = 0;
		while (str[str_i + j] != '\0' && str[str_i + j] != delim)
			j++;
		result[i] = malloc((j + 1) * sizeof(char));
		if (!result[i])
			return (free_result(result, i));
		j = 0;
		while (str[str_i + j] != delim && str[str_i + j] != '\0')
		{
			result[i][j] = str[str_i + j];
			j++;
		}
		result[i][j] = '\0';
		str_i += j;
		i++;
	}
	result[i] = NULL;
	return (result);
}
