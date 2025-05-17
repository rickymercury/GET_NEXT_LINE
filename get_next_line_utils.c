/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:16:04 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/17 12:15:22 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len] && str[len] != '\n' )
		len++;
	if (str[len] == '\n')
		len++;
	return (len);
}

char	*join_till_nl(char *line, const char *buffer)
{
	char	*new_line;
	int		line_idx;
	int		buffer_idx;

	if (!line)
	{
		line = malloc(1 * sizeof(char));
		if (!line)
			return (NULL);
		line[0] = '\0';
	}
	new_line = malloc(sizeof(char) * (ft_strlen(line) + ft_strlen(buffer) + 1));
	if (!new_line)
		return (NULL);
	line_idx = -1;
	while (line[++line_idx] != '\0')
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
