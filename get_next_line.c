/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:46:17 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/17 12:46:23 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*result_line;
	int			read_idx;
	int			write_idx;
	int			newline_found;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	result_line = NULL;
	newline_found = 0;
	while (!newline_found && (buffer[0] || (read(fd, buffer, BUFFER_SIZE) > 0)))
	{
		result_line = join_till_nl(result_line, buffer);
		read_idx = 0;
		write_idx = 0;
		while (buffer[read_idx] != '\0')
		{
			if (newline_found)
				buffer[write_idx++] = buffer[read_idx];
			if (buffer[read_idx] == '\n')
				newline_found = 1;
			buffer[read_idx++] = '\0';
		}
	}
	return (result_line);
}
