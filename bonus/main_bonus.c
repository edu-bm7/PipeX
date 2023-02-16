/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:23:56 by ebezerra          #+#    #+#             */
/*   Updated: 2023/02/09 23:26:43 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int argc, char *argv[])
{
	extern char	**environ;
	t_data		data;

	if (argc < 5)
	{
		ft_dprintf(STDERR_FILENO, "Usage:  ./pipex infile cmd1 cmd2 [cmdN] ");
		ft_dprintf(STDERR_FILENO, ". . . outfile\n");
		ft_dprintf(STDERR_FILENO, "\t./pipex here_doc LIMITER cmd1 cmd2");
		ft_dprintf(STDERR_FILENO, " [cmdN] . . . outfile\n");
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(argv[1], "here_doc") == 0 && argc < 6)
	{
		ft_dprintf(STDERR_FILENO, "Usage:  ./pipex infile cmd1 cmd2 [cmdN] ");
		ft_dprintf(STDERR_FILENO, ". . . outfile\n");
		ft_dprintf(STDERR_FILENO, ".\t/pipex here_doc LIMITER cmd1 cmd2");
		ft_dprintf(STDERR_FILENO, " [cmdN] . . . outfile\n");
		exit(EXIT_FAILURE);
	}
	forked_process_routine(argv, argc, environ, &data);
	return (0);
}
