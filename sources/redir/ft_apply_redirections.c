/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 15:30:00 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/06 01:49:18 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "heredoc.h"

static int	handle_redir_type(t_redir *redir, t_cmd *cmd, t_shell *shell)
{
	if (redir->type == REDIR_IN)
		return (redir_input(cmd, redir->file));
	if (redir->type == REDIR_OUT)
		return (redir_output(cmd, redir->file));
	if (redir->type == REDIR_APPEND)
		return (redir_append(cmd, redir->file));
	if (redir->type == REDIR_HEREDOC)
		return (ft_handle(cmd, redir->file, shell));
	return (1);
}

static int	dup_redirections(t_cmd *cmd)
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

int	apply_redirections(t_cmd *cmd)
{
	t_redir	*redir;
	int		ret;

	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	redir = cmd->redirs;
	while (redir)
	{
		ret = handle_redir_type(redir, cmd, NULL);
		if (ret != 0)
		{
			cleanup_fds(cmd);
			return (ret);
		}
		redir = redir->next;
	}
	return (dup_redirections(cmd));
}

int	apply_redirections_with_shell(t_cmd *cmd, t_shell *shell)
{
	t_redir	*redir;
	int		ret;

	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	redir = cmd->redirs;
	while (redir)
	{
		ret = handle_redir_type(redir, cmd, shell);
		if (ret != 0)
		{
			cleanup_fds(cmd);
			return (ret);
		}
		redir = redir->next;
	}
	return (dup_redirections(cmd));
}
