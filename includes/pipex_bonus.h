/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:52:57 by ebezerra          #+#    #+#             */
/*   Updated: 2023/02/09 22:59:47 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "libft.h"
# include "def_bonus.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct s_split
{
	int		count;
	char	**res;
	int		in_quote;
	int		len;
	int		i;
	int		j;
}				t_split;

typedef struct s_data
{
	pid_t	*pid;
	int		h_doc;
	int		status;
	int		last_status;
	int		cmd_num;
	int		**fd;
	int		inc;
	char	*str;
	char	*trim_str;
	char	*limiter;
	int		infile;
	int		outfile;
	char	*bin_file;
	char	*cmd_path;
	char	**cmd_args;
}				t_data;

void	forked_process_routine(char **argv, int argc, char **environ,
			t_data *data);
void	wait_for_processes(t_data *data);
char	*get_bin_name(const char *command);
void	pipe_write_to_stdout(int pipe_write, t_data *data);
void	pipe_read_to_stdin(int pipe_read, t_data *data);
void	input_file_to_stdin(int infile, t_data *data);
void	output_file_to_stdout(int outfile, t_data *data);
char	*cmd_path_routine(char *bin_file);
void	handle_exec_errors(char *cmd_path, char **cmd_args, t_data *data);
char	**split_with_quotes(const char *s);
t_bool	check_for_quotes(char *cmd);
void	initialize_data(t_data *data, int argc, char **argv);
int		**allocate_fd(int **fd, t_data *data);
int		**create_pipes(t_data *data);
void	free_vars(t_data *data);
void	wait_routine(t_data *data);
void	first_cmd_routine(t_data *data, char **argv, int i);
void	last_cmd_routine(t_data *data, char **argv, int i);
void	intermediates_cmd_routine(t_data *data, int i);
void	here_doc_routine(char **argv, t_data *data);
t_bool	check_outfile_error(int outfile);

#endif
