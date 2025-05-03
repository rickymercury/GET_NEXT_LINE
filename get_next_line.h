/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmedeiro <rmedeiro@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 14:49:39 by rmedeiro          #+#    #+#             */
/*   Updated: 2025/05/03 19:35:10 by rmedeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int		ft_strlen(const char *str);
char	*get_next_line(int fd);
char	*extract_line(char *getline);
char	*get_update(char *getline);
char	*ft_strchr(const char *s, int c);
char	*get_strjoin(char *s1, char const *s2);

#endif