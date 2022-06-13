/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 16:42:44 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/03 16:48:14 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_dict	*str_to_dict(char *key, char *value)
{
	t_dict	*node;

	node = malloc(sizeof(t_dict) * 1);
	if (!node)
		return (NULL);
	node->key = ft_strdup(key);
	if (!node->key)
	{
		free(node);
		return (NULL);
	}
	node->value = ft_strdup(value);
	if (!node->value)
	{
		free_simple(node->key, node, ERR);
		return (NULL);
	}
	return (node);
}

t_dict	*arr_to_dict(char *str)
{
	int		start;
	int		end;
	t_dict	*node;

	start = 0;
	node = malloc(sizeof(t_dict) * 1);
	if (!node)
		return (NULL);
	end = ft_strchr(str, '=') - str;
	node->key = ft_substr(str, start, end);
	if (!node->key)
	{
		free(node);
		return (NULL);
	}
	start = ++end;
	end = ft_strlen(&str[start]);
	node->value = ft_substr(str, start, end);
	if (!node->value)
	{
		free_simple(node->key, node, ERR);
		return (NULL);
	}
	return (node);
}
