/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:16:04 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/03 19:33:44 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	joined = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!joined)
		return (NULL);
	s1_idx = -1;
	while (s1[++s1_idx] != '\0')
		joined[s1_idx] = s1[s1_idx];
	s2_idx = 0;
	while (s2[s2_idx] != '\0')
		joined[s1_idx++] = s2[s2_idx++];
	joined[s1_idx] = '\0';
	free(s1);
	return (joined);
}

char	*ft_strchr(const char *s, int c)
{
	int	idx;

	if (!s)
		return (NULL);
	idx = 0;
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

char	*extract_line(char *getline)
{
	char	*returnline;
	int		idx;

	idx = 0;
	if (!getline[idx])
		return (NULL);
	while (getline[idx] != '\0' && getline[idx] != '\n')
		idx++;
	if (getline[idx] == '\n')
		idx++;
	returnline = malloc(sizeof(char) * (idx + 1));
	if (!returnline)
		return (NULL);
	idx = 0;
	while (getline[idx] != '\n' && getline[idx] != '\0')
	{
		returnline[idx] = getline[idx];
		idx++;
	}
	if (getline[idx] == '\n')
		returnline[idx++] = '\n';
	returnline[idx] = '\0';
	return (returnline);
}

char	*get_update(char *getline)
{
	char	*buffer;
	int		line_idx;
	int		buf_idx;

	line_idx = 0;
	while (getline[line_idx] != '\0' && getline[line_idx] != '\n')
		line_idx++;
	if (!getline[line_idx])
		return (free(getline), NULL);
	buffer = malloc(sizeof(char) * (ft_strlen(getline) - line_idx + 1));
	if (!buffer)
		return (NULL);
	line_idx++;
	buf_idx = 0;
	while (getline[line_idx + buf_idx] != '\0')
	{
		buffer[buf_idx] = getline[line_idx + buf_idx];
		buf_idx++;
	}
	buffer[buf_idx] = '\0';
	free(getline);
	return (buffer);
}
