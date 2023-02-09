/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:23:56 by ebezerra          #+#    #+#             */
/*   Updated: 2023/02/09 22:33:31 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[])
{
	int			fd[2];
	extern char	**environ;

	if (argc != 5)
	{
		ft_dprintf(STDERR_FILENO, "Error: Usage: ./pipex infile cmd1 cmd2 ");
		ft_dprintf(STDERR_FILENO, "outfile\n");
		exit(EXIT_FAILURE);
	}
	if (pipe(fd) == -1)
	{
		perror("Error: Pipe error");
		exit(EXIT_FAILURE);
	}
	forked_proccesses_routine(fd, argv, environ);
	return (0);
}
