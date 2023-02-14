/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_routine_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:40:08 by ebezerra          #+#    #+#             */
/*   Updated: 2023/02/09 22:42:29 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc_routine(char **argv, t_data *data)
{
	data->limiter = argv[2];
	data->infile = open(".temp_file.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (data->infile == -1)
	{
		ft_dprintf(STDERR_FILENO, "bash: .temp_file.txt: ");
		perror("");
	}
	ft_printf("> ");
	data->str = get_next_line(STDIN_FILENO);
	while (data->str != NULL)
	{
		data->trim_str = ft_strtrim(data->str, "\n");
		if (ft_strcmp(data->trim_str, data->limiter) == 0)
		{
			free(data->str);
			free(data->trim_str);
			break ;
		}
		write(data->infile, data->str, ft_strlen(data->str));
		free(data->str);
		free(data->trim_str);
		ft_printf("> ");
		data->str = get_next_line(STDIN_FILENO);
	}
	close(data->infile);
}
