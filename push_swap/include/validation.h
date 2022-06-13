#ifndef VALIDATION_H
# define VALIDATION_H

int		is_valid(char *s);
void	free_lst(t_list *stack);
void	error(t_list *stack, char **args, int format_error);

#endif
