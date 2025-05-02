/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 22:39:46 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/02 23:01:32 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	static char	*getline[1024];
	char		*returnline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	getline[fd] = get_read(getline[fd], fd);
	if (!getline[fd])
		return (free(getline[fd]), NULL);
	returnline = extract_line(getline[fd]);
	getline[fd] = get_update(getline[fd]);
	return (returnline);
}

char	*get_read(char *getline, int fd)
{
	char	*temp;
	int		check;

	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp)
		return (free(getline), NULL);
	check = 1;
	while (!ft_strchr(getline, '\n') && check != 0)
	{
		check = read(fd, temp, BUFFER_SIZE);
		if (check == -1)
		{
			free(temp);
			free(getline);
			return (NULL);
		}
		temp[check] = '\0';
		getline = get_strjoin(getline, temp);
	}
	free(temp);
	return (getline);
}

char	*extract_line(char *getline)
{
	char	*returnline;
	int		idx;

	idx = 0;
	if (!getline[idx])
		return (NULL);
	while (getline[idx] != '\0' && getline[idx] != '\n')
		idx++;
	if (getline[idx] == '\n')
		idx++;
	returnline = malloc(sizeof(char) * (idx + 1));
	if (!returnline)
		return (NULL);
	idx = 0;
	while (getline[idx] != '\n' && getline[idx] != '\0')
	{
		returnline[idx] = getline[idx];
		idx++;
	}
	if (getline[idx] == '\n')
		returnline[idx++] = '\n';
	returnline[idx] = '\0';
	return (returnline);
}

char	*get_update(char *getline)
{
	char	*buffer;
	int		line_idx;
	int		buf_idx;

	line_idx = 0;
	while (getline[line_idx] != '\0' && getline[line_idx] != '\n')
		line_idx++;
	if (!getline[line_idx])
		return (free(getline), NULL);
	buffer = malloc(sizeof(char) * (ft_strlen(getline) - line_idx));
	if (!buffer)
		return (NULL);
	line_idx++;
	buf_idx = 0;
	while (getline[line_idx + buf_idx] != '\0')
	{
		buffer[buf_idx] = getline[line_idx + buf_idx];
		buf_idx++;
	}
	buffer[buf_idx] = '\0';
	free(getline);
	return (buffer);
}
