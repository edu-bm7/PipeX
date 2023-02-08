//
// Created by eduardo on 1/24/23.
//

#include "pipex_bonus.h"

void	pipe_write_to_stdout(int pipe_write, t_data *data)
{
	if (dup2(pipe_write, STDOUT_FILENO) == -1)
	{
		perror("Error: dup2 PWtOut:");
		free_vars(data);
		exit(EXIT_FAILURE);
	}
}

void	pipe_read_to_stdin(int pipe_read, t_data *data)
{
	if (dup2(pipe_read, STDIN_FILENO) == -1)
	{
		perror("Error: dup2 PRtIn:");
		free_vars(data);
		exit(EXIT_FAILURE);
	}
}

void	input_file_to_stdin(int infile, t_data *data)
{
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		perror("Error: dup2 FitIN:");
		free_vars(data);
		exit(EXIT_FAILURE);
	}
}

void	output_file_to_stdout(int outfile, t_data *data)
{
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		perror("Error: dup2 FitOut:");
		free_vars(data);
		exit(EXIT_FAILURE);
	}
}
