/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forked_routine.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebezerra <ebezerra@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 22:34:10 by ebezerra          #+#    #+#             */
/*   Updated: 2023/02/09 22:34:54 by ebezerra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void		check_cmd_not_found(const char *cmd, char *bin_file);
static void		pid1_routine(int *fd, char **argv, char **environ);
static void		pid2_routine(int *fd, char **argv, char **environ);
static t_bool	check_outfile_error(int outfile);

void	forked_proccesses_routine(int *fd, char **argv, char **environ)
{
	pid_t	pid1;
	pid_t	pid2;

	pid1 = fork();
	if (pid1 == -1)
	{
		perror("Error: Fork error");
		exit(EXIT_FAILURE);
	}
	if (pid1 == 0)
		pid1_routine(fd, argv, environ);
	pid2 = fork();
	if (pid2 == -1)
	{
		perror("Error: Fork error");
		exit(EXIT_FAILURE);
	}
	if (pid2 == 0)
		pid2_routine(fd, argv, environ);
	close(fd[0]);
	close(fd[1]);
	wait_for_processes(pid1, pid2);
}

static void	pid1_routine(int *fd, char **argv, char **environ)
{
	int		infile;
	char	*bin_file1;
	char	*cmd1_path;
	char	**cmd1_args;

	close(fd[0]);
	infile = open(argv[1], O_RDONLY);
	check_infile_error(infile, argv);
	pipe_write_to_stdout(fd[1]);
	input_file_to_stdin(infile);
	close(infile);
	bin_file1 = get_bin_name(argv[2]);
	cmd1_path = cmd_path_routine(bin_file1);
	check_cmd_not_found(cmd1_path, bin_file1);
	if (check_for_quotes(argv[2]))
	{
		cmd1_args = split_with_quotes(argv[2]);
		invalid_num_quotes(cmd1_args, cmd1_path, bin_file1);
	}
	else
		cmd1_args = ft_split(argv[2], ' ');
	free(bin_file1);
	execve(cmd1_path, cmd1_args, environ);
	handle_exec_errors(cmd1_path, cmd1_args);
}

static void	pid2_routine(int *fd, char **argv, char **environ)
{
	int		outfile;
	char	*bin_file2;
	char	*cmd2_path;
	char	**cmd2_args;

	pipe_read_to_stdin(fd[0]);
	close(fd[1]);
	outfile = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (check_outfile_error(outfile))
		exit(EXIT_FAILURE);
	output_file_to_stdout(outfile);
	close(outfile);
	bin_file2 = get_bin_name(argv[3]);
	cmd2_path = cmd_path_routine(bin_file2);
	check_cmd_not_found(cmd2_path, bin_file2);
	if (check_for_quotes(argv[3]))
	{
		cmd2_args = split_with_quotes(argv[3]);
		invalid_num_quotes(cmd2_args, cmd2_path, bin_file2);
	}
	else
		cmd2_args = ft_split(argv[3], ' ');
	free(bin_file2);
	execve(cmd2_path, cmd2_args, environ);
	handle_exec_errors(cmd2_path, cmd2_args);
}

static t_bool	check_outfile_error(int outfile)
{
	if (outfile == -1)
	{
		perror("Error: ");
		return (true_);
	}
	return (false_);
}

static void	check_cmd_not_found(const char *cmd, char *bin_file)
{
	if (cmd == NULL)
	{
		ft_dprintf(STDERR_FILENO, "%s: command not found\n", bin_file);
		free(bin_file);
		exit(CMDNFND);
	}
}
