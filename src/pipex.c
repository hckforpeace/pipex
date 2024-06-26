/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:46:11 by pierre            #+#    #+#             */
/*   Updated: 2024/06/14 15:24:44 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

/* depending on the number of commands calls redirect_io to create children */
int	pipex(char **cmds, t_pipe data, int argc)
{
	int		i;
	pid_t	last_child;

	i = 3;
	last_child = redirect_io(data, cmds[2], READ_FROM_FILE);
	while (i < argc - 2)
	{
		last_child = redirect_io(data, cmds[i], PIPE);
		i++;
	}
	last_child = redirect_io(data, cmds[i], WRITE_TO_FILE);
	return (wait_children(last_child));
}

/* creates (pipe, children and redirects) */
int	redirect_io(t_pipe data, char *cmd, int flag)
{
	int	fd[2];
	int	child;

	if (pipe(fd) < 0)
		error_disp_exit("pipex: pipe: ", strerror(errno), 1);
	child = fork();
	if (child < 0)
		error_disp_exit("pipex: fork: ", strerror(errno), 1);
	else if (child == 0)
		redirect_files(cmd, data, fd, flag);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		error_disp_exit("pipex: dup2: ", strerror(errno), 1);
	close(fd[0]);
	return (child);
}

/* manages children behaviour depending on the flag */
void	redirect_files(char *cmd, t_pipe data, int *pipe, int flag)
{
	close(pipe[0]);
	if (flag == READ_FROM_FILE || flag == PIPE)
	{
		if (dup2(pipe[1], STDOUT_FILENO) < 0)
			error_disp_exit("pipex: dup2: ", strerror(errno), 1);
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

/* executes commands if they exists */
void	executer(t_pipe data, char *cmd)
{
	char	*path;
	char	**argv;

	if (!access(cmd, F_OK))
		path = cmd;
	else
	{
		argv = ft_split(cmd, ' ');
		path = gettest_path(get_paths(data.envp), argv[0]);
		if (!path)
		{
			clear_wordar(argv);
			error_disp_exit("pipex: path: ", "command not found", 127);
		}
	}
	if (execve(path, argv, data.envp) < 0)
	{
		free(path);
		clear_wordar(argv);
		error_disp_exit("pipex: exec: ", strerror(errno), 126);
	}
}
