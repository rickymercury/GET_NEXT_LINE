/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:55:15 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/10 23:22:50 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*result_line;
	size_t		idx;

	idx = 0;
	if (BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
	{
		if (fd >= 0 && fd <= FOPEN_MAX)
			while (buffer[fd][idx])
				buffer[fd][idx++] = '\0';
		return (NULL);
	}
	result_line = NULL;
	while (buffer[fd][0] || read(fd, buffer[fd], BUFFER_SIZE))
	{
		result_line = join_till_nl(result_line, buffer[fd]);
		if (manage_buffer(buffer[fd]))
			break ;
	}
	return (result_line);
}
