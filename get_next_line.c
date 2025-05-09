/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:46:17 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/09 23:29:06 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	buffer[BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer[0])
		read(fd, buffer, BUFFER_SIZE);
	line = NULL;
	while (buffer[0])
	{
		line = join_till_nl(line, buffer);
		if (!line)
			return (NULL);
		if (movebuffer(buffer) == 1)
			break ;
		if (read(fd, buffer, 0) < 0)
			return (free(line), NULL);
		read(fd, buffer, BUFFER_SIZE);
	}
	return (line);
}
