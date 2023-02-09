/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:37:56 by ebezerra          #+#    #+#             */
/*   Updated: 2023/02/09 22:37:58 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	pipe_write_to_stdout(int pipe_write, t_data *data)
{
	if (dup2(pipe_write, STDOUT_FILENO) == -1)
	{
		perror("bash: dup2");
		free_vars(data);
		exit(EXIT_FAILURE);
	}
}

void	pipe_read_to_stdin(int pipe_read, t_data *data)
{
	if (dup2(pipe_read, STDIN_FILENO) == -1)
	{
		perror("bash: dup2");
		free_vars(data);
		exit(EXIT_FAILURE);
	}
}

void	input_file_to_stdin(int infile, t_data *data)
{
	if (infile == -1)
	{
		free_vars(data);
		exit(EXIT_FAILURE);
	}
	if (dup2(infile, STDIN_FILENO) == -1)
	{
		perror("bash: dup2");
		free_vars(data);
		exit(EXIT_FAILURE);
	}
}

void	output_file_to_stdout(int outfile, t_data *data)
{
	if (dup2(outfile, STDOUT_FILENO) == -1)
	{
		perror("bash: dup2");
		free_vars(data);
		exit(EXIT_FAILURE);
	}
}
