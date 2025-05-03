/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 22:39:46 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/03 18:39:02 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*stash[1024];
	char		*buf;
	char		*line;
	int			rd;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (free(stash[fd]), NULL);
	rd = 1;
	while (!ft_strchr(stash[fd], '\n') && rd != 0)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1)
			return (free(buf), free(stash[fd]), stash[fd] = NULL, NULL);
		buf[rd] = '\0';
		stash[fd] = get_strjoin(stash[fd], buf);
	}
	free(buf);
	if (!stash[fd])
		return (NULL);
	line = extract_line(stash[fd]);
	stash[fd] = get_update(stash[fd]);
	return (line);
}
