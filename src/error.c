/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbeyloun <pbeyloun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:59:36 by pierre            #+#    #+#             */
/*   Updated: 2024/06/12 20:04:36 by pbeyloun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	error_disp(char *cmd, char *error_message)
{
	char	buffer[500];
	int		cmd_len;
	int		error_len;

	cmd_len = ft_strlen(cmd);
	error_len = ft_strlen(error_message);
	ft_memcpy(buffer, cmd, cmd_len);
	ft_memcpy(buffer + cmd_len, error_message, error_len);
	ft_memcpy(buffer + cmd_len + error_len + 1, "\n", 1);
	buffer[cmd_len + error_len + 1] = 0;
	write(STDERR_FILENO, buffer, error_len + cmd_len + 1);
}

void	error_disp_exit(char *cmd, char *error_message, int eno)
{
	char	buffer[500];
	int		cmd_len;
	int		error_len;

	cmd_len = ft_strlen(cmd);
	error_len = ft_strlen(error_message);
	ft_memcpy(buffer, cmd, cmd_len);
	ft_memcpy(buffer + cmd_len, error_message, error_len);
	ft_memcpy(buffer + cmd_len + error_len + 1, "\n", 1);
	buffer[cmd_len + error_len + 1] = 0;
	write(STDERR_FILENO, buffer, error_len + cmd_len + 1);
	exit(eno);
}
