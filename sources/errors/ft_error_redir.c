/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:55:00 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/06 01:08:52 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cleanup_fds(t_cmd *cmd)
{
	if (cmd->fd_in != STDIN_FILENO && cmd->fd_in > 2)
	{
		close(cmd->fd_in);
		cmd->fd_in = STDIN_FILENO;
	}
	if (cmd->fd_out != STDOUT_FILENO && cmd->fd_out > 2)
	{
		close(cmd->fd_out);
		cmd->fd_out = STDOUT_FILENO;
	}
}

int	ft_handle_redir_error(t_cmd *cmd, char *file, int error_code)
{
	ft_cleanup_fds(cmd);
	if (error_code == 1)
		perror(file);
	return (1);
}

int	ft_check_file_access(char *file, int mode)
{
	if (access(file, F_OK) == -1)
	{
		ft_put_error(file, NULL, "No such file or directory");
		return (1);
	}
	if (access(file, mode) == -1)
	{
		ft_put_error(file, NULL, "Permission denied");
		return (1);
	}
	return (0);
}
