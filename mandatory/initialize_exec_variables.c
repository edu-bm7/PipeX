/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_exec_variables.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:35:08 by ebezerra          #+#    #+#             */
/*   Updated: 2023/02/09 22:35:28 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

	if (ft_strcmp(bin_file, "") == 0)
	{
		ft_dprintf(STDERR_FILENO, "bash: '': command not found\n");
		free(bin_file);
		exit(CMDNFND);
	}
	if (ft_strchr(bin_file, '/') != NULL)
		return (ft_strdup(bin_file));
	if (access(bin_file, F_OK) != -1)
	{
		if (access(bin_file, X_OK) == -1)
		{
			ft_dprintf(STDERR_FILENO, "bash: %s: ", bin_file);
			perror("");
			free(bin_file);
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
