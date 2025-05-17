/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 23:33:12 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/17 12:58:50 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

#include <stdio.h>

int main(void)
{
	int	fd[2];
	char	*line[2];

	fd[0] = open("test.txt", O_RDONLY);
	fd[1] = open("test1.txt", O_RDONLY);
	while ((line[0] = get_next_line(fd[0])) != NULL
	&& (line[1] = get_next_line(fd[1])) != NULL)
	{
		printf("%s", line[0]);
		printf("%s", line[1]);
		free(line[0]);
		free(line[1]);
	}
	free(line[0]);
	free(line[1]);
	close(fd[0]);
	close(fd[1]);
	return 0;
}