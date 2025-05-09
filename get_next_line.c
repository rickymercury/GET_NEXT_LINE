/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:46:17 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/09 14:09:03 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE + 1];
    char *line;
    int rd;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    line = join_till_nl(NULL, buffer);
    if (!line)
        return (NULL);
    move_buffer(buffer);
    rd = 1;
    while (!(find_last_nl(line)) && rd > 0)
    {
        rd = read(fd, buffer, BUFFER_SIZE);
        if (rd <= 0)
            break ;
        line = join_till_nl(line, buffer);
        if (!line)
            return (NULL);
        move_buffer(buffer);
    }
    if (!line[0] || rd < 0)
        return (free(line), NULL);
    return (line);
}
