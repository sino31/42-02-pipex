/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shigematsuaono <shigematsuaono@student.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 16:54:11 by ashigema          #+#    #+#             */
/*   Updated: 2023/10/27 11:07:33 by shigematsua      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static char	*concat_str(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*result;
	size_t	len;
	size_t	len2;

	len = ft_strlen(s1);
	len2 = ft_strlen(s2);
	result = malloc((len + len2 + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (j < len)
		result[i++] = s1[j++];
	j = 0;
	while (j < len2)
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	if (s1 == NULL && s2 == NULL)
		return (NULL);
	else if (s1 == NULL)
		return (ft_strdup(s2));
	else if (s2 == NULL)
		return (ft_strdup(s1));
	return (concat_str(s1, s2));
}
