//
// Created by eduardo on 1/24/23.
//

#include "pipex_bonus.h"

void	handle_exec_errors(char *cmd_path, char **cmd_args, t_data *data)
{
	if (cmd_path)
	{
		free(cmd_path);
		free_str_array(cmd_args);
		free_vars(data);
		perror("Error: Is a directory");
		exit(NOTEXEC);
	}
	free(cmd_path);
	free_str_array(cmd_args);
	free_vars(data);
	perror("Error: ");
	exit(EXIT_FAILURE);
}
