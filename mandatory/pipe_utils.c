//
// Created by eduardo on 1/24/23.
//

#include "pipex.h"

void	pipe_write_to_stdout(int pipe_write)
{
	if (dup2(pipe_write, STDOUT_FILENO) == -1)
	{
		perror("Error: dup2:");
		exit(EXIT_FAILURE);
	}
}

void	pipe_read_to_stdin(int pipe_read)
{
	if (dup2(pipe_read, STDIN_FILENO) == -1)
	{
		perror("Error: dup2:");
		exit(EXIT_FAILURE);
	}
}

void	input_file_to_stdin(int infile)
{
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		perror("Error: dup2:");
		exit(EXIT_FAILURE);
	}
}

void	output_file_to_stdout(int outfile)
{
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		perror("Error: dup2:");
		exit(EXIT_FAILURE);
	}
}
