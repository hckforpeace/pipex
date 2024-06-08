/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 00:26:23 by pierre            #+#    #+#             */
/*   Updated: 2024/06/07 22:54:22 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char *get_paths(char **env)
{
	if (env == NULL)
		return (NULL);
	while (ft_strncmp("PATH=", *env, 5) != 0 && *env)
		env++;
	if (*env != NULL)
		return (*env + 5);
	return (NULL);
}

char *gettest_path(char *envpath, char *cmd)
{
	char *path;
	char **paths;
	int	cmd_len;
	int	i;

	i = 0;
	cmd_len = ft_strlen(cmd);
	paths = ft_split(envpath, ':');
	while (paths[i])
	{
		path = add_cmdtopath(paths, cmd, cmd_len, i);
		if (!path)
			return (NULL);
		if (!access(path, F_OK))
		{
			clear_wordar(paths);
			return (path);
		}
		free(path);
		i++;
	}
	clear_wordar(paths);
	return (NULL);
}

void	clear_wordar(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

char *add_cmdtopath(char **paths, char *cmd, int cmd_len, int idx)
{
	char *path;

	path = (char *)malloc(sizeof(char) * (cmd_len + ft_strlen(paths[idx]) + 2));
	if (!path)
	{
		clear_wordar(paths);
		return (NULL);
	}
	path[0] = 0;
	ft_strcat(path, paths[idx]);
	ft_strcat(path, "/");
	ft_strcat(path, cmd);
	return (path);
}