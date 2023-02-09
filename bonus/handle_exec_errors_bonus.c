/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exec_errors_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:37:17 by ebezerra          #+#    #+#             */
/*   Updated: 2023/02/09 22:37:18 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	handle_exec_errors(char *cmd_path, char **cmd_args, t_data *data)
{
	if (cmd_path)
	{
		ft_dprintf(STDERR_FILENO, "bash: %s: Is a directory\n", cmd_path);
		free(cmd_path);
		free_str_array(cmd_args);
		free_vars(data);
		exit(NOTEXEC);
	}
	free(cmd_path);
	free_str_array(cmd_args);
	free_vars(data);
	perror("bash: ");
	exit(EXIT_FAILURE);
}
