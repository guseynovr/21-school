/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:50:55 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 18:12:29 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "map.h"

# define FLOOR   1
# define CEILING 2
# define EAST    4
# define WEST    8
# define SOUTH   16
# define NORTH   32
# define MAP     63
# define START   128

typedef struct s_arr_func
{
	char	name;
	void	(*f)(t_map *, int *, char *);
}	t_arr_func;

int		init_map(t_map **map);
void	ft_err(char *message);
int		check_open(char *path);
int		check_ext(char *path, char *ext);
void	open_file(char *path, int *fd);
void	floor_func(t_map *map, int *status, char *path);
void	ceil_func(t_map *map, int *status, char *path);
int		len_arr(char **arr);
void	free_arr(char **name);
void	ea_func(t_map *map, int *status, char *path);
void	we_func(t_map *map, int *status, char *path);
void	so_func(t_map *map, int *status, char *path);
void	no_func(t_map *map, int *status, char *path);
void	valid_str_map(t_map *map, char *line, int *status);
int		parse_map(t_map *map, char *path);
void	parse_string(t_map *map, char *line, int *status);
char	**init_names(void);
void	valid_elem_str(t_map *map, char *line, int *status);
void	free_names(char **name);
int		valid_map(t_map *map);
void	check_correct_pos(char **map, int x, int y);
void	check_unnecesary_sym(char **map);
void	check_outer_borders(char **map);
void	check_player_availability(t_map *map);
void	check_zeroes(char **map);
void	get_player_pos(t_map *map, int x, int y, char dir);
int		fill_to_rectangle(t_map *map);
int		find_max_str(char **arr);

#endif
