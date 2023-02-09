/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:32:14 by ebezerra          #+#    #+#             */
/*   Updated: 2023/02/09 22:32:15 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	pipe_write_to_stdout(int pipe_write)
{
	if (dup2(pipe_write, STDOUT_FILENO) == -1)
	{
		perror("bash: dup2");
		exit(EXIT_FAILURE);
	}
}

void	pipe_read_to_stdin(int pipe_read)
{
	if (dup2(pipe_read, STDIN_FILENO) == -1)
	{
		perror("bash: dup2");
		exit(EXIT_FAILURE);
	}
}

void	input_file_to_stdin(int infile)
{
	if (infile == -1)
		exit(EXIT_FAILURE);
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		perror("bash: dup2");
		exit(EXIT_FAILURE);
	}
}

void	output_file_to_stdout(int outfile)
{
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		perror("bash: dup2");
		exit(EXIT_FAILURE);
	}
}
