//
// Created by eduardo on 1/24/23.
//
#include "libft.h"

char	*ft_getenv(const char *name)
{
	int			i;
	extern char	**environ;
	size_t		len;

	i = 0;
	len = ft_strlen(name);
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
			return (&environ[i][len + 1]);
		i++;
	}
	return (NULL);
}
