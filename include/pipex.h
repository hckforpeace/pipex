/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:43:39 by pierre            #+#    #+#             */
/*   Updated: 2024/06/07 22:50:02 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_pipe
{
    int infile;
    int outfile;
    int read;
    int write;
    char **envp;
    char *paths;
} t_pipe;

#include "../libft/includes/libft.h"
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>

int is_validfile(char *filename);
void    pipex(char **cmds, t_pipe *data, int argc);
char *get_paths(char **env);
char *gettest_path(char *envpath, char *cmd);
char *get_paths(char **env);
t_pipe	*init_data(int infile, int outfile, char **envp);
void work(t_pipe *data, int idx, char *cmd);
char *get_paths(char **env);
char *gettest_path(char *envpath, char *cmd);
void	executer(char *path, char **argv, t_pipe *data);
void    clear_close(t_pipe *data);
void clearchld_data(char *path, char **argv, t_pipe *data);
void	error_disp(char *cmd, char *error_message);
char    *get_path(char *cmd, char *paths, int cmd_len);
char    *add_cmdtopath(char **paths, char *cmd, int cmd_len, int idx);
void	clear_wordar(char **str);

#endif
