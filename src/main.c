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

#include "../include/pipex.h"

int main(int argc, char **argv, char **envp)
{
    int fd;
    int pipe[2];

    if (argc != 5)
    {
        ft_printf("wrong input: it should be ./exe file cmd1 cmd2 outfile");
        return (0);
    }
    return (0);
}

int is_validfile(char *filename)
{
    int fd;
    char *msg;

    msg = ft_strjoin("bash: ", filename);
    fd = open(filename, O_RDONLY);
    if (fd < 0)
        perror(msg);
    free(msg);
    return (fd);
}

