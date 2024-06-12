/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 01:28:30 by pierre            #+#    #+#             */
/*   Updated: 2024/06/12 17:36:23 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	domydoc(t_pipe data)
{
	int	fd[2];
	int	ret;

	if (pipe(fd) < 0)
	{
		perror("pipe");
		exit(1);
	}
	ret = fork();
	if (ret < 0)
		error_disp_exit("fork", strerror(errno), 127);
	if (ret == 0)
		heredoc_work(data.limiter, fd);
	wait(NULL);
	close(fd[1]);
	if (dup2(fd[0], STDIN_FILENO) < 0)
		error_disp_exit("dup2", strerror(errno), 127);
	close(fd[0]);
}

void heredoc_work(char *limiter, int *pipe_fd)
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
	fprintf(stderr, "**%s\n", line);
	if (!line)
		error_disp_exit("heredoc: ", "CTRL + d", 127);
	else
		free(line);
	close(pipe_fd[1]);
	exit(EXIT_SUCCESS);
}

/* 	char	*line;

	close(fd[0]);
	write(STDOUT_FILENO, "heredoc> ", 9);
	line = get_next_line(STDIN_FILENO);
	while (line && ft_strcmp(line, limiter))
	{
		write(fd[1], line, ft_strlen(line));
		free(line);
		write(STDOUT_FILENO, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
	}
	if (!line)
		error_disp_exit("here_doc", ": ctrl d", 127);
	free(line);
	close(fd[1]);
	exit(EXIT_SUCCESS); */