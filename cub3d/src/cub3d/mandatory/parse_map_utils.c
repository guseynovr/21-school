/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 18:11:22 by dgidget           #+#    #+#             */
/*   Updated: 2021/11/04 18:12:43 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	find_max_str(char **arr)
{
	int	i;
	int	tmp;

	i = -1;
	tmp = 0;
	while (arr[++i])
		if (tmp < (int)(ft_strlen(arr[i])))
			tmp = ft_strlen(arr[i]);
	return (tmp);
}
