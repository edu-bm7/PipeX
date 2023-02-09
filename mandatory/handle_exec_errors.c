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
		ft_dprintf(STDERR_FILENO, "bash: %s: Is a directory\n", cmd_path);
		free(cmd_path);
		free_str_array(cmd_args);
		exit(NOTEXEC);
	}
	free(cmd_path);
	free_str_array(cmd_args);
	perror("bash: ");
	exit(EXIT_FAILURE);
}
