#ifndef OPERATIONS_H
# define OPERATIONS_H

void	swap(t_list **stack, t_list **second, char *s);
void	push(t_list **from, t_list **to, char *s);
void	rotate(t_list **stack, t_list **second, char *s);
void	reverse_rotate(t_list **stack, t_list **second, char *s);

#endif
