/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:35:52 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/03 19:32:37 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAST_H
# define CAST_H

void	cast_rays(t_cub *cub);
int		is_wall(t_cub *cub, float x, float y, float angle);
int		find_first_horizontal(t_cub *cub, int angle, float *fp);
int		find_first_vertical(t_cub *cub, int angle, float *fp);

#endif
