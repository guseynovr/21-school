/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elem_func_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 15:52:58 by aarson            #+#    #+#             */
/*   Updated: 2021/11/01 12:21:24 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3d.h"
#include "get_next_line.h"
#include "parse.h"
#include "libft.h"

void	no_func(t_map *map, int *status, char *path)
{
	if ((*status & NORTH) == NORTH)
		ft_err("Parse error duplicate element");
	*status = *status | NORTH;
	check_open(path);
	map->resources.north = ft_strdup(path);
}

void	ea_func(t_map *map, int *status, char *path)
{
	if ((*status & EAST) == EAST)
		ft_err("Parse error duplicate element");
	*status = *status | EAST;
	check_open(path);
	map->resources.east = ft_strdup(path);
}

void	we_func(t_map *map, int *status, char *path)
{
	if ((*status & WEST) == WEST)
		ft_err("Parse error duplicate element");
	*status = *status | WEST;
	check_open(path);
	map->resources.west = ft_strdup(path);
}

void	so_func(t_map *map, int *status, char *path)
{
	if ((*status & SOUTH) == SOUTH)
		ft_err("Parse error duplicate element");
	*status = *status | SOUTH;
	check_open(path);
	map->resources.south = ft_strdup(path);
}
