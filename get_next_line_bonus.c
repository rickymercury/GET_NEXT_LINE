/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:55:15 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/17 12:56:55 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[FDOPEN][BUFFER_SIZE + 1];
	char		*result_line;
	int			read_idx;
	int			write_idx;
	int			newline_found;

	if (BUFFER_SIZE <= 0 ||fd < 0 || fd >= FDOPEN)
		return (NULL);
	result_line = NULL;
	newline_found = 0;
	while (!newline_found && (buffer[fd][0] || (read(fd, buffer[fd], BUFFER_SIZE) > 0)))
	{
		result_line = join_till_nl(result_line, buffer[fd]);
		read_idx = 0;
		write_idx = 0;
		while (buffer[fd][read_idx] != '\0')
		{
			if (newline_found)
				buffer[fd][write_idx++] = buffer[fd][read_idx];
			if (buffer[fd][read_idx] == '\n')
				newline_found = 1;
			buffer[fd][read_idx++] = '\0';
		}
	}
	return (result_line);
}
