//
// Created by eduardo on 1/24/23.
//

#include "pipex.h"

void	handle_exec_errors(char *cmd_path, char **cmd_args)
{
	if (cmd_path)
	{
		free(cmd_path);
		free_str_array(cmd_args);
		perror("Error: Is a directory");
		exit(NOTEXEC);
	}
	free(cmd_path);
	free_str_array(cmd_args);
	perror("Error: ");
	exit(EXIT_FAILURE);
}
