//
// Created by eduardo on 1/24/23.
//

#include "libft.h"

void	free_str_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}
