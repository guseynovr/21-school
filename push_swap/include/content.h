#ifndef CONTENT_H
# define CONTENT_H

# include "libft.h"

typedef struct s_item
{
	int	value;
	int	index;
	int	flag;
}	t_item;

int		get_value(t_list *lst);
int		get_index(t_list *lst);
int		get_flag(t_list *lst);

void	set_value(t_list *lst, int value);
void	set_index(t_list *lst, int index);
void	set_flag(t_list *lst, int index);

#endif
