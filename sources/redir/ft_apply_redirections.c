/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_apply_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 21:30:19 by zimbo             #+#    #+#             */
/*   Updated: 2026/04/09 21:30:23 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

static int	ft_handle_redir_type(t_redir *redir, t_cmd *cmd, t_shell *shell)
{
	if (redir->type == REDIR_IN)
		return (ft_redir_input(cmd, redir->file));
	if (redir->type == REDIR_OUT)
		return (ft_redir_output(cmd, redir->file));
	if (redir->type == redir_append)
		return (ft_redir_append(cmd, redir->file));
	if (redir->type == redir_heredoc)
		return (ft_handle(cmd, redir->file, shell));
	return (1);
}

static int	ft_dup_redirections(t_cmd *cmd)
{
	if (cmd->fd_in != STDIN_FILENO)
	{
		if (dup2(cmd->fd_in, STDIN_FILENO) < 0)
		{
			perror("dup2");
			return (1);
		}
		close(cmd->fd_in);
	}
	if (cmd->fd_out != STDOUT_FILENO)
	{
		if (dup2(cmd->fd_out, STDOUT_FILENO) < 0)
		{
			perror("dup2");
			return (1);
		}
		close(cmd->fd_out);
	}
	return (0);
}

int	ft_apply_redirections(t_cmd *cmd, t_shell *shell)
{
	t_redir	*redir;
	int		ret;

	if (cmd->fd_in != STDIN_FILENO && cmd->fd_in > 2)
		close(cmd->fd_in);
	if (cmd->fd_out != STDOUT_FILENO && cmd->fd_out > 2)
		close(cmd->fd_out);
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	redir = cmd->redirs;
	while (redir)
	{
		ret = ft_handle_redir_type(redir, cmd, shell);
		if (ret != 0)
		{
			ft_cleanup_fds(cmd);
			return (ret);
		}
		redir = redir->next;
	}
	return (ft_dup_redirections(cmd));
}
