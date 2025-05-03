/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:46:17 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/03 18:37:58 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*buf;
	char		*line;
	int			rd;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free(stash), NULL);
	rd = 1;
	while (!ft_strchr(stash, '\n') && rd != 0)
	{
		rd = read(fd, buf, BUFFER_SIZE);
		if (rd == -1)
			return (free(buf), free(stash), stash = NULL, NULL);
		buf[rd] = '\0';
		stash = get_strjoin(stash, buf);
	}
	free(buf);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = get_update(stash);
	return (line);
}
