/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:46:17 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/15 23:36:15 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		*result_line;
	int			bytes_read;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	result_line = NULL;
	bytes_read = 1;
	while (*buffer || (bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		if (bytes_read == -1)
			return (free(result_line), NULL);
		result_line = join_till_nl(result_line, buffer);
		if (!result_line)
			return (NULL);
		if (manage_buffer(buffer))
			break ;
	}
	if (!result_line || result_line[0] == '\0')
		return (free(result_line), NULL);
	return (result_line);
}
