/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:45:11 by ruslan            #+#    #+#             */
/*   Updated: 2021/10/03 16:41:48 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(int argc, char **argv, t_list **env_lst)
{
	(void) argc;
	(void) argv;
	ft_lstiter(*env_lst, print_env_lst);
	return (OK);
}
