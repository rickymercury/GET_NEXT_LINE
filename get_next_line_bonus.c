/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 21:55:15 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/19 20:07:50 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*result_line;
	size_t		read_idx;
	size_t		write_idx;
	int			newl;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd >= FOPEN_MAX)
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

/* int	main(void)
{
	int		fd1 = open("test1.txt", O_RDONLY);
	int		fd2 = open("test2.txt", O_RDONLY);
	int		fd3 = open("test3.txt", O_RDONLY);
	char	*line1;
	char	*line2;
	char	*line3;

	if (fd1 < 0 || fd2 < 0 || fd3 < 0)
		return (1);

	while (1)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		line3 = get_next_line(fd3);

		if (!line1 && !line2 && !line3)
			break ;

		if (line1)
		{
			printf("test1: %s", line1);
			free(line1);
		}
		if (line2)
		{
			printf("test2: %s", line2);
			free(line2);
		}
		if (line3)
		{
			printf("test3: %s", line3);
			free(line3);
		}
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
} */