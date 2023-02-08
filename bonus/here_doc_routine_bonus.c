//
// Created by eduardo on 2/6/23.
//
#include "pipex_bonus.h"

void here_doc_routine(char **argv, t_data *data)
{
	data->limiter = argv[2];
	data->infile = open(".temp_file.txt", O_WRONLY | O_CREAT | O_APPEND, 0666);
	if (data->infile == -1)
		perror("Error:");
	ft_printf("> ");
	data->str = get_next_line(STDIN_FILENO);
	while (data->str != NULL)
	{
		data->trim_str = ft_strtrim(data->str, "\n");
		if(ft_strcmp(data->trim_str, data->limiter) == 0)
		{
			free(data->trim_str);
			break;
		}
		write(data->infile, data->str, ft_strlen(data->str));
		free(data->str);
		free(data->trim_str);
		ft_printf("> ");
		data->str = get_next_line(STDIN_FILENO);
	}
	close(data->infile);
	data->infile = open(".temp_file.txt", O_RDONLY);
	input_file_to_stdin(data->infile, data);
	unlink(".temp_file.txt");
	close(data->infile);
	exit (0);
}
