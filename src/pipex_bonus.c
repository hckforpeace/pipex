/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 01:25:47 by pierre            #+#    #+#             */
/*   Updated: 2024/06/12 21:19:56 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	pipex_bonus(char **cmds, t_pipe data, int argc)
{
	int		i;
	pid_t	last_child;

	i = 3;
	if (data.heredoc)
		domydoc(data);
	else
		last_child = redirect_io(data, cmds[2], READ_FROM_FILE);
	while (i < argc - 2)
	{
		last_child = redirect_io(data, cmds[i], PIPE);
		i++;
	}
	if (data.heredoc)
		last_child = redirect_io(data, cmds[i], HERE_DOC);
	else
		last_child = redirect_io(data, cmds[i], WRITE_TO_FILE);
	return (wait_children(last_child));
}

int	redirect_io(t_pipe data, char *cmd, int flag)
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
	return (child);
}

void	redirect_files(char *cmd, t_pipe data, int *pipe, int flag)
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
			redirect(data.infile, flag);
		executer(data, cmd);
		return ;
	}
	close(pipe[1]);
	redirect(data.outfile, flag);
	executer(data, cmd);
}

void	executer(t_pipe data, char *cmd)
{
	char	*path;
	char	**argv;

	argv = ft_split(cmd, ' ');
	path = gettest_path(get_paths(data.envp), argv[0]);
	if (!path)
	{
		error_disp(cmd, ": command not found");
		clear_wordar(argv);
		exit(127);
	}
	if (execve(path, argv, data.envp) < 0)
	{
		error_disp(cmd, ": command invoked can not execute");
		free(path);
		clear_wordar(argv);
		exit(126);
	}
}
