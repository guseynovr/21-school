/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 19:38:46 by aarson            #+#    #+#             */
/*   Updated: 2021/11/03 14:16:30 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render.h"
#include "get_next_line.h"
#include "libft.h"
#include "parse.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	t_map	*map;

	if (ac != 2)
		ft_err("Bad argument");
	if (!(init_map(&map)) || !(check_ext(av[1], ".cub")) || !(parse_map(map,
				av[1])) || !(valid_map(map)) || !(fill_to_rectangle(map)))
		ft_err("Parser error");
	start(map);
	return (0);
}
