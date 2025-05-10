/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:46:17 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/10 23:12:26 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*result_line;
	size_t		idx;

	idx = 0;
	if (BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
	{
		while (idx <= BUFFER_SIZE)
			buffer[idx++] = '\0';
		return (NULL);
	}
	result_line = NULL;
	while (buffer[0] || (read(fd, buffer, BUFFER_SIZE) > 0))
	{
		result_line = join_till_nl(result_line, buffer);
		if (manage_buffer(buffer))
			break ;
	}
	return (result_line);
}
