/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgidget <dgidget@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 16:38:13 by dgidget           #+#    #+#             */
/*   Updated: 2021/10/04 12:23:47 by dgidget          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*init_env(char **raw_env)
{
	t_dict		*node;
	t_list		*new_lst;
	t_list		*full_lst;

	full_lst = NULL;
	while (*++raw_env)
	{
		node = arr_to_dict(*raw_env);
		if (!node)
		{
			ft_lstiter(full_lst, clear_dict);
			return (NULL);
		}
		new_lst = ft_lstnew(node);
		if (!new_lst)
		{
			clear_dict(node);
			ft_lstclear(&full_lst, clear_dict);
			return (NULL);
		}
		ft_lstadd_back(&full_lst, new_lst);
	}
	set_shelllvl(&full_lst);
	return (full_lst);
}

t_dict	*get_var(char *key, t_list *lst)
{
	t_dict	*node;

	while (lst)
	{
		node = lst->content;
		if (!(ft_strcmp(key, node->key)))
			return (node);
		lst = lst->next;
	}
	return (NULL);
}

int	update_var(char *key, char *value, t_list *head, t_dict	*node)
{
	while (head)
	{
		node = head->content;
		if (!(ft_strcmp(key, node->key)))
		{
			node->value = ft_strdup(value);
			if (!node->value)
				return (ERR);
		}
		head = head->next;
	}
	return (OK);
}

int	set_var(char *key, char *value, t_list **lst)
{
	t_dict	*node;
	t_dict	*new_node;
	t_list	*new_lst;

	node = get_var(key, *lst);
	if (!node)
	{
		new_node = str_to_dict(key, value);
		if (!new_node)
			return (ERR);
		new_lst = ft_lstnew(new_node);
		if (!new_lst)
		{
			clear_dict(new_node);
			return (ERR);
		}
		ft_lstadd_front(lst, new_lst);
		return (OK);
	}
	return (update_var(key, value, *lst, node));
}

void	del_var(char *key, t_list **lst)
{
	t_list	*head;
	t_list	*tmp;

	tmp = *lst;
	if (!ft_strcmp(((t_dict *)tmp->content)->key, key))
	{
		head = tmp->next;
		ft_lstdelone(tmp, clear_dict);
		*lst = head;
		return ;
	}
	while (tmp)
	{
		head = tmp->next;
		if (!head)
			return ;
		if (!ft_strcmp(((t_dict *)head->content)->key, key))
		{
			tmp->next = head->next;
			ft_lstdelone(head, clear_dict);
			return ;
		}
		tmp = tmp->next;
	}
}
