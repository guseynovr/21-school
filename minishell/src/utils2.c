/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 13:49:04 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/03 22:37:42 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *s)
{
	char	*delimiter;
	int		namelen;
	char	*key;

	namelen = ft_strlen(s);
	delimiter = ft_strchr(s, '=');
	if (delimiter)
		namelen = delimiter - s;
	key = ft_substr(s, 0, namelen);
	if (!key)
		return (NULL);
	return (key);
}

char	*get_value(char *s)
{
	char	*delimiter;
	int		namelen;
	char	*value;

	namelen = ft_strlen(s);
	delimiter = ft_strchr(s, '=');
	if (delimiter)
		namelen = delimiter - s + 1;
	value = ft_substr(s + namelen, 0, ft_strlen(s + namelen));
	if (!value)
		return (NULL);
	return (value);
}

int	is_path_specified(char *s)
{
	return (ft_strchr(s, '/') || !ft_strncmp(s, "./", 2)
		|| !ft_strncmp(s, "../", 3));
}

void	clear_dict(void *del_node)
{
	t_dict	*node;

	node = del_node;
	free(node->key);
	free(node->value);
	free(node);
}

void	print_env_lst(void *p)
{
	t_dict	*node;

	node = p;
	printf("%s=%s\n", node->key, node->value);
}
