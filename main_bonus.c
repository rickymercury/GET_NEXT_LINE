/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 23:33:12 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/17 14:32:27 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

#include <stdio.h>

int main(void)
{
	int fd;
	int fd2;
	int i = 0;

	fd = open("test.txt", O_RDONLY);
	fd2 = open("test1.txt", O_RDONLY);
	while (i < 194)
	{
		printf("%s", get_next_line(fd));
		printf("%s", get_next_line(fd2));
	}
	return (0);
}