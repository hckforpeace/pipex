/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 01:28:30 by pierre            #+#    #+#             */
/*   Updated: 2024/06/14 13:55:32 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"
/* creates a child to manage the here doc and waits for it to end */

void	domydoc(t_pipe data)
{
	int	fd[2];
	int	ret;

	if (pipe(fd) < 0)
		error_disp_exit("pipex: pipe: ", strerror(errno), 1);
	ret = fork();
	if (ret < 0)
		error_disp_exit("fork", strerror(errno), 1);
	if (ret == 0)
		heredoc_work(data.limiter, fd);
	wait(NULL);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		error_disp_exit("dup2", strerror(errno), 1);
	close(fd[0]);
}
/* child read on STDIN until reading limiter its writes every time 
	on pipe[1] */

void	heredoc_work(char *limiter, int *pipe_fd)
{
	int		limiter_len;
	char	*line;

	limiter_len = ft_strlen(limiter);
	close(pipe_fd[0]);
	write(STDOUT_FILENO, "here_doc > ", 11);
	line = get_next_line(STDIN_FILENO);
	while (line && !(ft_strncmp(limiter, line, limiter_len) == 0
			&& line[limiter_len] == '\n'))
	{
		write(pipe_fd[1], line, ft_strlen(line));
		free(line);
		write(STDOUT_FILENO, "here_doc > ", 11);
		line = get_next_line(STDIN_FILENO);
	}
	if (!line)
		error_disp_exit("heredoc: ", "CTRL + d", 127);
	else
		free(line);
	close(pipe_fd[1]);
	exit(EXIT_SUCCESS);
}
/* waits for all children */

int	wait_children(pid_t last_child)
{
	int	status;
	int	retcode;

	while (ECHILD != errno)
	{
		if (waitpid(0, &status, 0) == last_child)
		{
			if (WIFEXITED(status))
				retcode = WEXITSTATUS(status);
			else
				retcode = WSTOPSIG(status);
		}
	}
	return (retcode);
}
