/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:55:15 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/17 14:42:17 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[FDOPEN + 1][BUFFER_SIZE + 1];
	char		*result_line;
	size_t		read_idx;
	size_t		write_idx;
	int			newl;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= FDOPEN)
		return (NULL);
	result_line = NULL;
	newl = 0;
	while (!newl && (buffer[fd][0] || (read(fd, buffer[fd], BUFFER_SIZE) > 0)))
	{
		result_line = join_till_nl(result_line, buffer[fd]);
		read_idx = 0;
		write_idx = 0;
		while (buffer[fd][read_idx] != '\0')
		{
			if (newl)
				buffer[fd][write_idx++] = buffer[fd][read_idx];
			if (buffer[fd][read_idx] == '\n')
				newl = 1;
			buffer[fd][read_idx++] = '\0';
		}
	}
	return (result_line);
}
