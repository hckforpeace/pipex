/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:46:11 by pierre            #+#    #+#             */
/*   Updated: 2024/06/04 19:18:33 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../include/pipex.h";

void	pipex(char **cmds, char **envp, t_pipe content)
{
	int	pid;
	int	i;
	t_disp *data;

	i = 1;
	data = init_data(data);
	if (content.fd < 0)
		i++;
	while (cmds[i])
	{
		if (fork() == 0)
		{
			;
		}
		i++;
	}
}

t_pipe	*init_data(int filed)
{
	int fd[2];
	t_pipe *data;

	if (pipe(fd) < 0)
	{
		perror("bash: pipe");
		exit(errno);
	}

	data = (t_pipe *)malloc(sizeof(struct s_pipe));
	data->fd = (int *)malloc(sizeof(int));
	data->read = (int *)malloc(sizeof(int));
	data->write = (int *)malloc(sizeof(int));

	*(data->fd) = filed;
	*(data->read) = fd[0];
	*(data->write) = fd[1];
	return (data);
}

void	clear_pipe(t_pipe *data)
{
	free(data->fd);
	free(data->read);
	free(data->write);
	free(data);
}

void work(t_pipe *data, int idx, char **env)
{
	if (idx == 1)
	{
		dup2(*data->fd, STDIN_FILENO);
		dup2(STDOUT_FILENO, data->write);
	}
	execve();
}