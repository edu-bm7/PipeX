/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:37:31 by ebezerra          #+#    #+#             */
/*   Updated: 2023/02/09 22:37:32 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	**fd_alloc_routine(int **fd, int cmd_num);

void	initialize_data(t_data *data, int argc, char **argv)
{
	if (ft_strcmp(argv[1], "here_doc") == 0)
		data->h_doc = 1;
	else
		data->h_doc = 0;
	if (data->h_doc)
	{
		data->inc = 3;
		data->cmd_num = argc - 4;
	}
	else
	{
		data->inc = 2;
		data->cmd_num = argc - 3;
	}
	data->fd = NULL;
	data->fd = allocate_fd(data->fd, data);
	data->pid = ft_calloc(data->cmd_num, sizeof (*data->pid));
	data->fd = create_pipes(data);
	data->status = 0;
	data->last_status = 0;
	data->bin_file = "";
	data->cmd_path = "";
}

int	**create_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->cmd_num - 1)
	{
		if (pipe(data->fd[i]) == -1)
		{
			perror("bash");
			free_vars(data);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (data->fd);
}

int	**allocate_fd(int **fd, t_data *data)
{
	fd = ft_calloc(data->cmd_num - 1, sizeof (*fd));
	if (!fd)
	{
		perror("bash");
		exit(EXIT_FAILURE);
	}
	return (fd_alloc_routine(fd, data->cmd_num));
}

static int	**fd_alloc_routine(int **fd, int cmd_num)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < cmd_num - 1)
	{
		fd[i] = ft_calloc(2, sizeof (**fd));
		if (!fd[i])
		{
			perror("bash");
			while (j < i)
			{
				free(fd[j]);
				j++;
			}
			free(fd);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (fd);
}
