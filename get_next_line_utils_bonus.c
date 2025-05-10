/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:00:59 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/10 23:18:09 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static size_t	ft_strlen(const char *str)
{
	size_t	idx;

	if (!str)
		return (0);
	idx = 0;
	while (str[idx])
		idx++;
	return (idx);
}

char	*join_till_nl(char *line, const char *buffer)
{
	char	*new_line;
	int		line_idx;
	int		buffer_idx;

	if (!line)
	{
		line = malloc(1 * sizeof(char));
		line[0] = '\0';
	}
	new_line = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(buffer) + 1));
	if (!new_line)
		return (NULL);
	line_idx = -1;
	while (line && line[++line_idx] != '\0')
		new_line[line_idx] = line[line_idx];
	buffer_idx = 0;
	while (buffer[buffer_idx] != '\0' && buffer[buffer_idx] != '\n')
		new_line[line_idx++] = buffer[buffer_idx++];
	if (buffer[buffer_idx] == '\n')
		new_line[line_idx++] = '\n';
	new_line[line_idx] = '\0';
	free(line);
	return (new_line);
}

int	manage_buffer(char *buffer)
{
	size_t	idx1;
	size_t	idx2;
	int		found_nl;

	found_nl = 0;
	idx1 = 0;
	while (buffer[idx1])
	{
		if (buffer[idx1] == '\n')
		{
			found_nl = 1;
			idx1++;
			break ;
		}
		idx1++;
	}
	idx2 = 0;
	while (buffer[idx1])
		buffer[idx2++] = buffer[idx1++];
	while (idx2 < idx1)
		buffer[idx2++] = '\0';
	return (found_nl);
}
