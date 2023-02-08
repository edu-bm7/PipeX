//
// Created by eduardo on 1/24/23.
//
#include "pipex.h"

static char	*get_cmd_path(const char *command);

char	*get_bin_name(const char *command)
{
	char	*bin_name;
	char	*arg;

	bin_name = ft_strdup(command);
	arg = ft_strchr(bin_name, ' ');
	if (arg)
		*arg = '\0';
	return (bin_name);
}

char	*cmd_path_routine(char *bin_file)
{
	char	*cmd_path;

	if (access(bin_file, F_OK) != -1)
	{
		if (access(bin_file, X_OK) == -1)
		{
			perror("Error: ");
			exit(NOTEXEC);
		}
	}
	if (access(bin_file, F_OK) == -1 && access(bin_file, X_OK) == -1)
		cmd_path = get_cmd_path(bin_file);
	else
		cmd_path = ft_strdup(bin_file);
	return (cmd_path);
}

static char	*get_cmd_path(const char *command)
{
	char	*path;
	char	**dir;
	char	*cmd_path;
	char	*tmp;
	int		i;

	path = ft_getenv("PATH");
	dir = ft_split(path, ':');
	i = 0;
	while (dir[i])
	{
		tmp = ft_strjoin(dir[i], "/");
		cmd_path = ft_strjoin(tmp, command);
		free(tmp);
		if (access(cmd_path, X_OK) == 0)
			break ;
		free(cmd_path);
		cmd_path = NULL;
		i++;
	}
	i = 0;
	while (dir[i])
		free(dir[i++]);
	free(dir);
	return (cmd_path);
}
