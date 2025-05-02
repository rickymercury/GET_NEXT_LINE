/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 22:36:18 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/02 23:00:35 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(const char *str)
{
	int	idx;

	idx = 0;
	while (str[idx] != '\0')
		idx++;
	return (idx);
}

char	*get_strjoin(char *s1, char const *s2)
{
	char	*joined;
	int		s1_idx;
	int		s2_idx;

	if (!s1)
	{
		s1 = malloc(1 * sizeof(char));
		*s1 = '\0';
	}
	joined = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!joined)
		return (NULL);
	s1_idx = -1;
	while (s1[++s1_idx] != '\0')
		joined[s1_idx] = s1[s1_idx];
	s2_idx = 0;
	while (s2[s2_idx] != '\0')
	{
		joined[s1_idx] = s2[s2_idx];
		s1_idx++;
		s2_idx++;
	}
	joined[s1_idx] = '\0';
	free(s1);
	return (joined);
}

char	*ft_strchr(const char *s, int c)
{
	int	idx;

	idx = 0;
	if (!s)
		return (NULL);
	while (s[idx] != '\0')
	{
		if (s[idx] == c)
			return ((char *)(s + idx));
		idx++;
	}
	if (s[idx] == c)
		return ((char *)(s + idx));
	return (NULL);
}
