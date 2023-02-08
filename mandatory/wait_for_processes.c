//
// Created by eduardo on 1/24/23.
//

#include "pipex.h"

static char	*get_signal_description(int sig);

void	wait_for_processes(pid_t pid1, pid_t pid2)
{
	int		child1_status;
	int		child2_status;
	char	*description;

	waitpid(pid1, &child1_status, 0);
	waitpid(pid2, &child2_status, 0);
	if (WIFEXITED(child2_status))
		exit(WEXITSTATUS(child2_status));
	else
	{
		if (WIFSIGNALED(child2_status))
		{
			description = get_signal_description(WTERMSIG(child2_status));
			ft_dprintf(STDERR_FILENO, "%s", description);
			if (WCOREDUMP(child2_status))
				ft_dprintf(STDERR_FILENO, " (core dumped)");
			if (description != NULL)
				ft_dprintf(STDERR_FILENO, "\n");
			exit(EXIT_OFFSET + WTERMSIG(child2_status));
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
