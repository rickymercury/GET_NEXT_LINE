/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 23:33:12 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/10 22:13:29 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	main(void)
{
	int fd[3];

	fd[0] = open("AP1", O_RDONLY);
	fd[2] = open("AP2", O_RDONLY);
	fd[1] = open("AP3", O_RDONLY);
	char *test1 = get_next_line(fd[0]);
	char *test2 = get_next_line(fd[1]);
	char *test3 = get_next_line(fd[2]);
	while (test1 || test2 || test3)
	{
		printf("test1: %s\n", test1);
		printf("test2: %s\n", test2);
		printf("test3: %s\n", test3);
		test1 = get_next_line(fd[0]);
		test2 = get_next_line(fd[1]);
		test3 = get_next_line(fd[2]);
	}
	free(test1);
	free(test2);
	free(test3);

	close(fd[0]);
	close(fd[1]);
	close(fd[2]);
}

#include <stdio.h>
int main(void)
{
	int	fd[2];
	char	*line[2];

	fd[0] = open("lol.txt", O_RDONLY);
	fd[1] = open("lol2.txt", O_RDONLY);
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