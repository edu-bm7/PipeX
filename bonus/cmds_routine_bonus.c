/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_routine_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:38:10 by ebezerra          #+#    #+#             */
/*   Updated: 2023/02/09 22:39:18 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	first_cmd_routine(t_data *data, char **argv, int i)
{
	close(data->fd[i][0]);
	if (ft_strcmp(argv[1], "here_doc") != 0)
	{
		data->infile = open(argv[1], O_RDONLY);
		if (data->infile == -1)
		{
			ft_dprintf(STDERR_FILENO, "bash: %s:", argv[1]);
			perror("");
		}
		input_file_to_stdin(data->infile, data);
		close(data->infile);
	}
	else
	{
		data->infile = open(".temp_file.txt", O_RDONLY);
		input_file_to_stdin(data->infile, data);
		unlink(".temp_file.txt");
		close(data->infile);
	}
	pipe_write_to_stdout(data->fd[i][1], data);
}

void	intermediates_cmd_routine(t_data *data, int i)
{
	close(data->fd[i - 1][1]);
	close(data->fd[i][0]);
	pipe_read_to_stdin(data->fd[i - 1][0], data);
	pipe_write_to_stdout(data->fd[i][1], data);
}

void	last_cmd_routine(t_data *data, char **argv, int i)
{
	close(data->fd[i - 1][1]);
	pipe_read_to_stdin(data->fd[i - 1][0], data);
	if (ft_strcmp(argv[1], "here_doc") == 0)
		data->outfile = open(argv[data->cmd_num + data->inc],
				O_CREAT | O_APPEND | O_WRONLY, 0666);
	else
		data->outfile = open(argv[data->cmd_num + data->inc],
				O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (check_outfile_error(data->outfile))
	{
		free_vars(data);
		exit(EXIT_FAILURE);
	}
	output_file_to_stdout(data->outfile, data);
	close(data->outfile);
}

t_bool	check_outfile_error(int outfile)
{
	if (outfile == -1)
	{
		perror("bash: ");
		return (true_);
	}
	return (false_);
}

void	free_vars(t_data *data)
{
	int	i;

	i = 0;
	if (data->fd && data->pid)
	{
		while (i < data->cmd_num - 1)
		{
			free(data->fd[i]);
			i++;
		}
		free(data->fd);
		free(data->pid);
	}
	data->fd = NULL;
	data->pid = NULL;
}
