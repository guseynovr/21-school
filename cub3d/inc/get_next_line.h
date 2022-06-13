/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:51:20 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/03 12:51:20 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

int		get_next_line(int fd, char **line);
int		check_n(char *s);
int		ft_strlena(const char *s);
char	*ft_strjoina(char const *s1, char const *s2);
char	*check_buf(char *buf, char *line, int *flg);

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif
#endif
