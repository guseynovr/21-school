#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include "operations.h"
# include "quicksort.h"
# include "content.h"
# include "find.h"
# include "validation.h"
# include "consts.h"

# include <stdio.h>

typedef struct s_info
{
	int	next;
	int	mid;
	int	max;
	int	flag;
}	t_info;

void	set_indexes(t_list *a);
t_list	*init_stack(int argc, char **argv);
void	quicksort(int *arr, int lo, int hi);

void	sort(t_list **a, t_list **b);
int		is_sorted(t_list *a, t_list *b, int end);
long	cmp(t_list *lst1, t_list *lst2);

void	mv_top(int place, t_list **lst, char *ro, char *rro);
void	mark_sorted(t_list **a, t_list **b, t_info *info, int in_a);
void	sort_five(t_list **a, t_list **b);
void	sort_five_r(t_list **a, t_list **b, t_info *info);
void	calc_info(t_list *a, t_info *info);

#endif
