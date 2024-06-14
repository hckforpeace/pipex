/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:46:11 by pierre            #+#    #+#             */
/*   Updated: 2024/06/14 13:47:46 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipe	data;

	if (argc != 5)
		error_disp_exit("error:", " wrong input", 1);
	data = init_data(argv, argc, envp);
	return (pipex(argv, data, argc));
}
/* init the struct t_pipe and makes (works for bonus and mandatory) */

t_pipe	init_data(char **argv, int argc, char **envp)
{
	t_pipe	data;

	data.heredoc = 0;
	data.limiter = NULL;
	data.outfile = argv[argc - 1];
	data.infile = argv[1];
	data.envp = envp;
	return (data);
}
/* Opens file, (depending on the flag) and redirects the fd on STDIN or STDOUT*/

void	redirect(char *file, int flag)
{
	int	fd;

	if (flag == READ_FROM_FILE)
		fd = open(file, O_RDONLY);
	else if (flag == WRITE_TO_FILE)
		fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	else
		fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0664);
	if (fd < 0)
		error_disp_exit(file, ": open error", 1);
	if (flag == READ_FROM_FILE)
	{
		if (dup2(fd, STDIN_FILENO) < 0)
			error_disp_exit("dup2: ", strerror(errno), 1);
	}
	if (flag == WRITE_TO_FILE || flag == HERE_DOC)
	{
		if (dup2(fd, STDOUT_FILENO) < 0)
			error_disp_exit("dup2: ", strerror(errno), 1);
	}
	close(fd);
}
