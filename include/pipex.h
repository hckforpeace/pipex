/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pierre <pierre@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 23:43:39 by pierre            #+#    #+#             */
/*   Updated: 2024/06/03 23:44:37 by pierre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

typedef struct s_pipe
{
    int *fd;
    int *read;
    int *write;
} t_pipe;

#include "../libft/includes/libft.h"
#include <stdio.h>
#include <errno.h>

int is_validfile(char *filename);
#endif