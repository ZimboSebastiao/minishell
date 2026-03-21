/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft_executor_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:05:00 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/08 02:55:07 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_check_cmd_access(t_cmd *c, t_shell *sh)
{
	char	*path;

	if (ft_is_builtin(c->args[0]))
		return (1);
	path = ft_resolve_path(c->args[0], sh->env_list);
	if (!path)
	{
		if (ft_strchr(c->args[0], '/'))
		{
			if (access(c->args[0], F_OK) == -1)
				sh->exit = 127;
			else if (access(c->args[0], X_OK) == -1)
				sh->exit = 126;
		}
		else
			sh->exit = 127;
		ft_put_error(c->args[0], NULL, "command not found\n");
		return (0);
	}
	free(path);
	return (1);
}

int	ft_validate_cmd(t_cmd *cmd, t_shell *sh)
{
	t_redir	*redir;
	int		ret;

	ret = ft_check_cmd_access(cmd, sh);
	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type != redir_heredoc)
		{
			if (redir->type == REDIR_IN && access(redir->file, R_OK) == -1)
			{
				perror(redir->file);
				sh->exit = 1;
				ret = 0;
			}
		}
		redir = redir->next;
	}
	return (ret);
}
