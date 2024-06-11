/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:46:11 by pierre            #+#    #+#             */
/*   Updated: 2024/06/11 22:58:49 by pierre           ###   ########.fr       */
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
    data = init_data(argv[argc - 1], argv[1], envp);
    pipex(argv, data, argc);
    return (0);
}

t_pipe	init_data(char *outfile, char *infile, char **envp)
{
    t_pipe  data;

    data.outfile = outfile;
    data.infile = infile;
    data.envp = envp;
	return (data);
}


