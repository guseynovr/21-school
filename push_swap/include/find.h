#ifndef FIND_H
# define FIND_H

# include "libft.h"
# include "content.h"

int		find_min(t_list *lst);
int		find_max(t_list *lst);
long	next(t_list *lst, int min, int max);
int		optimize_place(int place, int size);

#endif
