/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_append.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 21:32:03 by zimbo             #+#    #+#             */
/*   Updated: 2026/04/09 21:32:06 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_redir_append(t_cmd *cmd, char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		perror(file);
		return (1);
	}
	if (cmd->fd_out != STDOUT_FILENO && cmd->fd_out > 2)
		close(cmd->fd_out);
	cmd->fd_out = fd;
	return (0);
}
