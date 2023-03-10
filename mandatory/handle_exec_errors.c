/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec_errors.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:33:54 by ebezerra          #+#    #+#             */
/*   Updated: 2023/02/09 22:33:56 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_exec_errors(char *cmd_path, char **cmd_args)
{
	if (cmd_path)
	{
		if (access(cmd_path, F_OK) == 0 && access(cmd_path, R_OK) == 0)
		{
			ft_dprintf(STDERR_FILENO, "bash: %s: Is a directory\n", cmd_path);
			free(cmd_path);
			free_str_array(cmd_args);
			exit(NOTEXEC);
		}
		else
		{
			ft_dprintf(STDERR_FILENO, "bash: %s: ", cmd_path);
			ft_dprintf(STDERR_FILENO, "No such file or directory\n");
			free(cmd_path);
			free_str_array(cmd_args);
			exit(CMDNFND);
		}
	}
	free(cmd_path);
	free_str_array(cmd_args);
	perror("bash: ");
	exit(EXIT_FAILURE);
}

void	invalid_num_quotes(char **cmd_args, char *cmd_path, char *bin_file)
{
	if (!cmd_args)
	{
		free(cmd_path);
		ft_dprintf(STDERR_FILENO, "%s: Invalid number of quotes\n", bin_file);
		free(bin_file);
		exit(EXIT_FAILURE);
	}
}

void	check_infile_error(int infile, char **argv)
{
	if (infile == -1)
	{
		ft_dprintf(STDERR_FILENO, "bash: %s: ", argv[1]);
		perror("");
	}
}
