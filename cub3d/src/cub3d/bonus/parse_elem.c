/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 12:47:48 by aarson            #+#    #+#             */
/*   Updated: 2021/11/01 12:21:29 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "cub3d.h"
#include "get_next_line.h"
#include "libft.h"
#include "parse.h"
#include <stdio.h>

static void	init_arr_func(t_arr_func *func)
{
	func[0].name = 'F';
	func[0].f = floor_func;
	func[1].name = 'C';
	func[1].f = ceil_func;
	func[2].name = 'E';
	func[2].f = ea_func;
	func[3].name = 'W';
	func[3].f = we_func;
	func[4].name = 'S';
	func[4].f = so_func;
	func[5].name = 'N';
	func[5].f = no_func;
}

void	valid_elem_str(t_map *map, char *line, int *status)
{
	t_arr_func	func[6];
	int			i;
	char		**arr;

	i = -1;
	init_arr_func(func);
	arr = ft_split(line, ' ');
	if (!arr || len_arr(arr) != 2)
		ft_err("Parse map error, invalid element string");
	while (++i < 6)
		if (func[i].name == line[0])
			func[i].f(map, status, arr[1]);
	free_arr(arr);
}

void	free_names(char **name)
{
	int	i;

	i = -1;
	while (++i < 7)
		free(name[i]);
	free(name);
}

char	**init_names(void)
{
	char	**name;
	int		i;

	name = malloc(sizeof(char *) * 7);
	name[0] = ft_strdup("SO");
	name[1] = ft_strdup("NO");
	name[2] = ft_strdup("WE");
	name[3] = ft_strdup("EA");
	name[4] = ft_strdup("F");
	name[5] = ft_strdup("C");
	name[6] = 0;
	i = -1;
	while (++i < 6)
	{
		if (!name[i])
		{
			free_names(name);
			ft_err("Malloc");
		}
	}
	return (name);
}
