/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:46:11 by pierre            #+#    #+#             */
/*   Updated: 2024/06/08 20:06:42 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	pipex(char **cmds, t_pipe *data, int argc)
{
	int	i;
	i = 2;

	if (data->infile < 0)
				i++;
	while (i < argc - 1)
	{
		if (fork() == 0)
		{
			work(data, i, cmds[i]);
			exit(EXIT_SUCCESS);
		}
		i++;
	}
	while(i < 2)
	{
		wait(NULL);
		i++;
	}
}

void work(t_pipe *data, int idx, char *cmd)
{
	char *path;
	char **argv;

	argv = ft_split(cmd, ' ');
	path = gettest_path(data->paths, argv[0]);
	if (idx == 2)
	{
		close(data->outfile);
		close(data->read);
		dup2(data->infile, STDIN_FILENO);
		dup2(data->write, STDOUT_FILENO);
	}
	else
	{
		close(data->infile);
		close(data->write);
		dup2(data->read, STDIN_FILENO);
		dup2(data->outfile, STDOUT_FILENO);
	}
	executer(path, argv, data);
}

void	executer(char *path, char **argv, t_pipe *data)
{
	int i = 0;
	while (argv[i])
	{
		fprintf(stderr,"%s\n", argv[i]);
		i++;
	}
	fprintf(stderr, "%s\n", path);
	if (execve(path, argv, data->envp) < 0)
	{
		error_disp(argv[0], ": command not found\n");
		clearchld_data(path, argv, data);
		exit(127);
	}
}

void clearchld_data(char *path, char **argv, t_pipe *data)
{
	clear_wordar(argv);
	free(path);
	clear_close(data);
}
