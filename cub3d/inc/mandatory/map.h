/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 12:47:41 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/03 12:48:44 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

typedef struct s_resources
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	unsigned int	floor;
	unsigned int	ceiling;
}	t_resources;

typedef struct s_map
{
	char		**map;
	int			size[2];
	int			player[2];
	int			player_dir;
	t_resources	resources;
}	t_map;

#endif
