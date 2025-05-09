/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 22:00:59 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/09 23:22:30 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static int	linelen(const char *str)
{
	int	idx;

	if (!str)
		return (0);
	idx = 0;
	while (str[idx] && str[idx] != '\n')
		idx++;
	if (str[idx] == '\n')
		idx++;
	return (idx);
}

char	*join_till_nl(char *s1, const char *s2)
{
	char	*line;
	int		s1_idx;
	int		s2_idx;

	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	line = malloc(sizeof(char) * (linelen(s1) + linelen(s2) + 1));
	if (!line)
		return (free(s1), NULL);
	s1_idx = -1;
	while (s1[++s1_idx])
		line[s1_idx] = s1[s1_idx];
	s2_idx = 0;
	while (s2[s2_idx] && s2[s2_idx] != '\n')
		line[s1_idx++] = s2[s2_idx++];
	if (s2[s2_idx] == '\n')
		line[s1_idx++] = '\n';
	line[s1_idx] = '\0';
	free(s1);
	return (line);
}

int	movebuffer(char *buffer)
{
	int	r_idx;
	int	w_idx;
	int	found_nl;

	r_idx = 0;
	found_nl = 0;
	while (buffer[r_idx] && buffer[r_idx] != '\n')
		r_idx++;
	if (buffer[r_idx] == '\n')
	{
		r_idx++;
		found_nl = 1;
	}
	w_idx = 0;
	while (buffer[r_idx] && r_idx < BUFFER_SIZE)
		buffer[w_idx++] = buffer[r_idx++];
	while (w_idx < BUFFER_SIZE)
		buffer[w_idx++] = '\0';
	return (found_nl);
}
