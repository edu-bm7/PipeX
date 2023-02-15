/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forked_routine_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:36:20 by ebezerra          #+#    #+#             */
/*   Updated: 2023/02/09 22:36:44 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void		check_cmd_not_found(const char *cmd, t_data *data,
					char *bin_file);
static void		child_proc_routine(char **argv, char **environ,
					t_data *data, int i);
static void		parent_proc_routine(t_data *data, int i);

void	forked_process_routine(char **argv, int argc,
									char **environ, t_data *data)
{
	int	i;

	i = 0;
	initialize_data(data, argc, argv);
	if (ft_strcmp(argv[1], "here_doc") == 0)
		here_doc_routine(argv, data);
	while (i < data->cmd_num)
	{
		data->pid[i] = fork();
		if (data->pid[i] == -1)
		{
			perror("bash");
			free_vars(data);
			exit(EXIT_FAILURE);
		}
		else if (data->pid[i] == 0)
			child_proc_routine(argv, environ, data, i);
		else
			parent_proc_routine(data, i);
		i++;
	}
	wait_routine(data);
}

static void	child_proc_routine(char **argv, char **environ, t_data *data, int i)
{
	if (i == 0)
		first_cmd_routine(data, argv, i);
	if (i == data->cmd_num - 1)
		last_cmd_routine(data, argv, i);
	if (i > 0 && i < data->cmd_num - 1)
		intermediates_cmd_routine(data, i);
	data->bin_file = get_bin_name(argv[i + data->inc]);
	data->cmd_path = cmd_path_routine(data->bin_file, data);
	check_cmd_not_found(data->cmd_path, data, data->bin_file);
	free(data->bin_file);
	if (check_for_quotes(argv[i + data->inc]))
		data->cmd_args = split_with_quotes(argv[i + data->inc]);
	else
		data->cmd_args = ft_split(argv[i + data->inc], ' ');
	execve(data->cmd_path, data->cmd_args, environ);
	handle_exec_errors(data->cmd_path, data->cmd_args, data);
}

static void	parent_proc_routine(t_data *data, int i)
{
	if (i > 0)
	{
		close(data->fd[i - 1][0]);
		close(data->fd[i - 1][1]);
	}
}

static void	check_cmd_not_found(const char *cmd, t_data *data, char *bin_file)
{
	if (cmd == NULL)
	{
		ft_dprintf(STDERR_FILENO, "%s: command not found\n", bin_file);
		free_vars(data);
		free(bin_file);
		exit(CMDNFND);
	}
}
