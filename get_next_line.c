/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:46:17 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/19 20:10:03 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*result_line;
	size_t		read_idx;
	size_t		write_idx;
	int			newl;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	result_line = NULL;
	newl = 0;
	while (!newl && (buffer[0] || (read(fd, buffer, BUFFER_SIZE) > 0)))
	{
		result_line = join_till_nl(result_line, buffer);
		read_idx = 0;
		write_idx = 0;
		while (buffer[read_idx] != '\0')
		{
			if (newl)
				buffer[write_idx++] = buffer[read_idx];
			if (buffer[read_idx] == '\n')
				newl = 1;
			buffer[read_idx++] = '\0';
		}
	}
	return (result_line);
}

/* #include <stdio.h>

int main(void)
{
	int fd = open("test1.txt", O_RDONLY);
	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	printf("%c", '\n');
	close(fd);
	return 0;
} */