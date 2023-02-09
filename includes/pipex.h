/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 20:26:16 by ebezerra          #+#    #+#             */
/*   Updated: 2023/02/09 22:52:27 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include "def.h"
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

void		forked_proccesses_routine(int *fd, char **argv, char **environ);
void		wait_for_processes(pid_t pid1, pid_t pid2);
char		*get_bin_name(const char *command);
void		pipe_write_to_stdout(int pipe_write);
void		pipe_read_to_stdin(int pipe_read);
void		input_file_to_stdin(int infile);
void		output_file_to_stdout(int outfile);
char		*cmd_path_routine(char *bin_file);
void		handle_exec_errors(char *cmd_path, char **cmd_args);
char		**split_with_quotes(const char *s);
t_bool		check_for_quotes(char *cmd);

#endif