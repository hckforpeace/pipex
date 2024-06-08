/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:46:11 by pierre            #+#    #+#             */
/*   Updated: 2024/06/08 19:47:30 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int main(int argc, char **argv, char **envp)
{
    int infile;
    int outfile;
    t_pipe  *data;
    
    if (argc != 5)
    {
        error_disp("error :", "worng input");
        return (0);
    }
    infile = is_validfile(argv[1]);
    outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0664);
    data = init_data(infile, outfile, envp);
    pipex(argv, data, argc);
    clear_close(data);
    return (0);
}

t_pipe	*init_data(int infile, int outfile, char **envp)
{
	int fd[2];
	t_pipe *data;

	if (pipe(fd) < 0)
	{
		error_disp("pipe", "pipe failed\n");
		exit(errno);
	}

	data = (t_pipe *)malloc(sizeof(struct s_pipe));

	data->infile = infile;
    data->outfile = outfile;
	data->read = fd[0];
	data->write = fd[1];
    data->envp = envp;
    data->paths = get_paths(envp);
	return (data);
}

void    clear_close(t_pipe *data)
{
    close(data->infile);
	close(data->outfile);
	close(data->read);
	close(data->write);
    free(data);
}

int is_validfile(char *filename)
{
    int fd;

    fd = open(filename, O_RDONLY);
    if (fd < 0)
        error_disp(filename, ": no such file or directory\n");
    return (fd);
}
