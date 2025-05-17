/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:00:59 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/17 14:13:48 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] != '\0' && str[len] != '\n' )
		len++;
	if (str[len] == '\n')
		len++;
	return (len);
}

char	*join_till_nl(char *line, char *buffer)
{
	char	*new_line;
	size_t	line_idx;
	size_t	buffer_idx;

	if (!buffer)
		return (NULL);
	new_line = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(buffer) + 1));
	if (!new_line)
		return (NULL);
	line_idx = 0;
	while (line && line[line_idx] != '\0')
	{
		new_line[line_idx] = line[line_idx];
		line_idx++;
	}
	buffer_idx = 0;
	while (buffer[buffer_idx] != '\0')
	{
		new_line[line_idx++] = buffer[buffer_idx];
		if (buffer[buffer_idx++] == '\n')
			break ;
	}
	new_line[line_idx] = '\0';
	free(line);
	return (new_line);
}
