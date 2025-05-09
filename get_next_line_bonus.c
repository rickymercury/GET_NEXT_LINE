/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:55:15 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/09 22:15:44 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	int			rd;

	if (fd < 0 || fd >= FOPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	line = join_till_nl(NULL, buffer[fd]);
	if (!line)
		return (NULL);
	move_buffer(buffer[fd]);
	rd = 1;
	while (!find_last_nl(line) && rd > 0)
	{
		rd = read(fd, buffer[fd], BUFFER_SIZE);
		if (rd <= 0)
			break ;
		buffer[fd][rd] = '\0';
		line = join_till_nl(line, buffer[fd]);
		if (!line)
			return (NULL);
		move_buffer(buffer[fd]);
	}
	if (!line[0] || rd < 0)
		return (free(line), NULL);
	return (line);
}
