/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:43:39 by pierre            #+#    #+#             */
/*   Updated: 2024/06/12 21:18:44 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# define READ_FROM_FILE 1
# define PIPE 2
# define WRITE_TO_FILE 3
# define HERE_DOC 4

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>

typedef struct s_pipe
{
	char	*outfile;
	char	*infile;
	char	**envp;
	int		heredoc;
	char	*limiter;
}	t_pipe;

int		pipex(char **cmds, t_pipe data, int argc);
int		pipex_bonus(char **cmds, t_pipe data, int argc);
int		redirect_io(t_pipe data, char *cmd, int flag);
void	redirect_files(char *cmd, t_pipe data, int *pipe, int flag);
void	executer(t_pipe data, char *cmd);
char	*get_paths(char **env);
char	*gettest_path(char *envpath, char *cmd);
void	clear_wordar(char **str);
char	*add_cmdtopath(char **paths, char *cmd, int cmd_len, int idx);
t_pipe	init_data(char **argv, int argc, char **envp);
void	error_disp(char *cmd, char *error_message);
void	error_disp_exit(char *cmd, char *error_message, int eno);
int		wait_children(pid_t last_child);

// heredoc bonus

void	domydoc(t_pipe data);
void	heredoc_work(char *limiter, int *pipe_fd);
void	redirect(char *file, int flag);

#endif
