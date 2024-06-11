/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:43:39 by pierre            #+#    #+#             */
/*   Updated: 2024/06/11 22:54:40 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define READ_FROM_FILE 1
# define PIPE 2
# define WRITE_TO_FILE 3

typedef struct s_pipe
{
    char    *outfile;
    char    *infile;
    char    **envp;
} t_pipe;

#include "../libft/includes/libft.h"
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>

void	pipex(char **cmds, t_pipe data, int argc);
void redirect_io(t_pipe data, char *cmd, int flag);
void redirect_files(char *cmd , t_pipe data, int *pipe, int flag);
void	executer(t_pipe data, char *cmd);
void redirect_infile(char *infile);
void	redirect_outfile(char *outfile);
char *get_paths(char **env);
char *gettest_path(char *envpath, char *cmd);
void	clear_wordar(char **str);
char *add_cmdtopath(char **paths, char *cmd, int cmd_len, int idx);
t_pipe	init_data(char *outfile, char *infile, char **envp);
void	error_disp(char *cmd, char *error_message);
void	error_disp_exit(char *cmd, char *error_message, int eno);

#endif
