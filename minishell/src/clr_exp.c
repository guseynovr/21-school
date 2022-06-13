/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clr_exp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 15:33:07 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/04 18:18:43 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	clr_exp(t_exp *exp, int status)
{
	ft_lstclear(exp->lst, free);
	free(exp);
	return (status);
}
