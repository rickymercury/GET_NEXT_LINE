/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:55:15 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/16 00:03:48 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE];
	char		*result_line;
	int			bytes_read;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= FOPEN_MAX)
		return (NULL);
	result_line = NULL;
	bytes_read = 1;
	while (*buffer[fd] || bytes_read > 0)
	{
		if (!*buffer[fd])
			bytes_read = read(fd, buffer[fd], BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(result_line), NULL);
		result_line = join_till_nl(result_line, buffer[fd]);
		if (!result_line)
			return (NULL);
		if (manage_buffer(buffer[fd]))
			break ;
	}
	if (!result_line || result_line[0] == '\0')
		return (free(result_line), NULL);
	return (result_line);
}
