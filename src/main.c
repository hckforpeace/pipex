/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:46:11 by pierre            #+#    #+#             */
/*   Updated: 2024/06/12 17:43:44 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int main(int argc, char **argv, char **envp)
{
    t_pipe  data;
    
    if (argc < 5)
    {
        error_disp("error :", "worng input");
        exit(1);
    }
    data = init_data(argv, argc, envp);
    pipex(argv, data, argc);
    return (0);
}

t_pipe	init_data(char **argv, int argc, char **envp)
{
    t_pipe  data;

    data.envp = envp;
    if (!ft_strcmp("here_doc", argv[1]))
    {
        data.heredoc = 1;
        data.limiter = argv[2];
        data.outfile = argv[argc - 1];
        data.infile = NULL;
    }
    else
    {
        if (argc < 5)
            error_disp_exit("pipex: ", "wrong input !", 1);
        data.heredoc = 0;
        data.limiter = NULL;
        data.outfile = argv[argc - 1];
        data.infile = argv[1];
    }
	return (data);
}


