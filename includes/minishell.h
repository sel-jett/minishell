#ifndef MINISHELL_H
#define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>


typedef struct s_data
{
	void			*data;
	struct s_data	*next;
}	t_data;

void	*my_malloc(size_t size, int mode);

#endif
