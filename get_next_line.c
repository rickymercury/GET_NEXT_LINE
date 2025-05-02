/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:46:17 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/02 22:13:46 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*getline;
	char		*returnline;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	getline = get_read(getline, fd);
	if (!getline)
		return (free(getline), NULL);
	returnline = extract_line(getline);
	getline = get_update(getline);
	return (returnline);
}
