/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:16:04 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/09 12:25:37 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int linelen(const char *str)
{
    int idx = 0;

    if (!str)
        return (0);
    while (str[idx] && str[idx] != '\n')
        idx++;
    if (str[idx] == '\n')
        idx++;
    return (idx);
}

char *join_till_nl(char *s1, const char *s2)
{
    char *line;
    int s1_idx, s2_idx;

    if (!s1)
    {
        s1 = malloc(1);
        s1[0] = '\0';
    }
    line = malloc(sizeof(char) * (linelen(s1) + linelen(s2) + 1));
    if (!line)
        return (free(s1), NULL);
    s1_idx = 0;
    while (s1[s1_idx])
    {
        line[s1_idx] = s1[s1_idx];
        s1_idx++;
    }
    s2_idx = 0;
    while (s2[s2_idx] && s2[s2_idx] != '\n')
        line[s1_idx++] = s2[s2_idx++];
    if (s2[s2_idx] == '\n')
        line[s1_idx++] = '\n';
    line[s1_idx] = '\0';
    free(s1);
    return (line);
}

char *ft_strrchr_nl(const char *s)
{
    int idx;

    if (!s)
        return (NULL);
	idx = 0;
    while (s[idx])
        idx++;
    while (idx >= 0)
    {
        if (s[idx] == '\n')
            return ((char *)(s + idx));
        idx--;
    }
    return (NULL);
}

void *zero_buffer(char *buffer, size_t size)
{
    size_t idx;

	idx = 0;
    while (idx < size)
        buffer[idx++] = 0;
    return (NULL);
}

void trim_buffer(char *buffer)
{
    int r_idx;
	int w_idx;
	
	r_idx = 0;
    while (buffer[r_idx] && buffer[r_idx] != '\n')
        r_idx++;
    if (buffer[r_idx] == '\n')
        r_idx++;
	w_idx = 0;
    while (buffer[r_idx] && r_idx < BUFFER_SIZE)
        buffer[w_idx++] = buffer[r_idx++];
    zero_buffer(&buffer[w_idx], BUFFER_SIZE - w_idx);
}