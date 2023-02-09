/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_for_processes_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:37:47 by ebezerra          #+#    #+#             */
/*   Updated: 2023/02/09 22:37:48 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static char	*get_signal_description(int sig);

void	wait_routine(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_num)
	{
		if (i == data->cmd_num - 1)
		{
			waitpid(data->pid[i], &data->last_status, 0);
			wait_for_processes(data);
		}
		else
			waitpid(data->pid[i], &data->status, 0);
		++i;
	}
}

void	wait_for_processes(t_data *data)
{
	char	*description;

	if (WIFEXITED(data->last_status))
	{
		free_vars(data);
		exit(WEXITSTATUS(data->last_status));
	}
	else
	{
		if (WIFSIGNALED(data->last_status))
		{
			description = get_signal_description(WTERMSIG(data->last_status));
			ft_dprintf(STDERR_FILENO, "%s", description);
			if (WCOREDUMP(data->last_status))
				ft_dprintf(STDERR_FILENO, " (core dumped)");
			if (description != NULL)
				ft_dprintf(STDERR_FILENO, "\n");
			free_vars(data);
			exit(EXIT_OFFSET + WTERMSIG(data->last_status));
		}
	}
}

static char	*get_signal_description(int sig)
{
	static char	*descriptions[EXIT_OFFSET] = {
	[SIGHUP] = "Hangup",
	[SIGQUIT] = "Quit",
	[SIGILL] = "Illegal instruction",
	[SIGTRAP] = "Trace/breakpoint trap",
	[SIGABRT] = "Aborted",
	[SIGFPE] = "Floating point exception",
	[SIGKILL] = "Killed",
	[SIGSEGV] = "Segmentation fault",
	[SIGALRM] = "Alarm clock",
	[SIGTERM] = "Terminated",
	};

	return (descriptions[sig]);
}
