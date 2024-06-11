/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:46:11 by pierre            #+#    #+#             */
/*   Updated: 2024/06/11 23:07:23 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	pipex(char **cmds, t_pipe data, int argc)
{
	int	i;

	i = 3;
	redirect_io(data, cmds[2], READ_FROM_FILE);
	while (i < argc - 2)
	{
		redirect_io( data, cmds[i], PIPE);
		i++;
	}
	redirect_io(data, cmds[i], WRITE_TO_FILE);
	i = 0;
	while (i < argc - 3)
	{
		wait(NULL);
		i++;
	}
}

void redirect_io(t_pipe data, char *cmd, int flag)
{
	int	fd[2];
	int	child;
	if (pipe(fd) < 0)
	{
		perror("pipe");
		exit(1);
	}
	child = fork();
	if (child < 0)
	{
		perror("fork");
		exit(1);
	}
	else if (child == 0)
		redirect_files(cmd, data, fd, flag);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(1);
	}
	close(fd[0]);
}

void redirect_files(char *cmd , t_pipe data, int *pipe, int flag)
{

	close(pipe[0]);
	if (flag == READ_FROM_FILE || flag == PIPE)
	{
		if (dup2(pipe[1], STDOUT_FILENO) < 0)
		{
			perror("dup2");
			exit(1);
		}
		close(pipe[1]);
		if (flag == READ_FROM_FILE)
			redirect_infile(data.infile);
		executer(data, cmd);
		return ;
	}
	close(pipe[1]);
	redirect_outfile(data.outfile);
	executer(data, cmd);
	
}
void	executer(t_pipe data, char *cmd)
{
	char *path;
	char **argv;
	
	argv = ft_split(cmd, ' ');
	path = gettest_path(get_paths(data.envp), argv[0]);
	if (!path)
	{
		error_disp(cmd, ": command not found\n");
		clear_wordar(argv);
		exit(127);
	}
	if (execve(path, argv, data.envp) < 0)
	{
		error_disp(cmd, ": command invoked can not execute\n");
		free(path);
		clear_wordar(argv);
		exit(126);
	}
}
void	redirect_outfile(char *outfile)
{
	int	fd;

	fd = open(outfile, O_WRONLY |  O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		error_disp_exit(outfile, ": open error", 1);
	if (dup2(fd, STDOUT_FILENO) < 0)
	{
		perror("dup2");
		exit(1);
	}
	close(fd);
}

void redirect_infile(char *infile)
{
	int	fd;

	fd = open(infile, O_RDONLY);
	if (fd < 0)
		error_disp_exit(infile, ": open error", 1);
	if (dup2(fd, STDIN_FILENO) < 0)
	{
		perror("dup2");
		exit(1);
	}
	close(fd);
}
