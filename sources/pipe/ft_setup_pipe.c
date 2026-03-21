/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setup_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 15:30:00 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/06 01:48:04 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_setup_pipe(t_cmd *cmd, int pipe_fd[2])
{
	if (!cmd->next)
		return (0);
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	cmd->fd_out = pipe_fd[1];
	cmd->next->fd_in = pipe_fd[0];
	cmd->has_pipe = 1;
	return (0);
}
