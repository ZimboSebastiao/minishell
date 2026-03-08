/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 01:12:09 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/08 01:08:49 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_single_builtin(t_cmd *cmd, t_shell *sh, int cmd_ok)
{
	if (!cmd_ok)
		return (1);
	sh->exit_status = run_builtin(cmd, sh);
	return (0);
}

static int	process_command(t_cmd *tmp, t_shell *sh, int p[2], int *prev_pipe)
{
	int	cmd_ok;

	tmp->fd_in = STDIN_FILENO;
	tmp->fd_out = STDOUT_FILENO;
	tmp->has_pipe = 0;
	if (setup_pipe(tmp, p))
		return (1);
	cmd_ok = resolve_cmd(tmp, sh);
	if (tmp->next || !is_builtin(tmp->args[0]))
		fork_and_exec(tmp, sh, cmd_ok);
	else if (cmd_ok)
		exec_single_builtin(tmp, sh, cmd_ok);
	close_fds(tmp, p, *prev_pipe);
	if (tmp->next)
		*prev_pipe = p[0];
	return (0);
}

int	executor(t_cmd *list, t_shell *sh)
{
	t_cmd	*tmp;
	int		p[2];
	int		prev_pipe;

	prev_pipe = -1;
	tmp = list;
	while (tmp)
	{
		if (process_command(tmp, sh, p, &prev_pipe) != 0)
			return (1);
		tmp = tmp->next;
	}
	wait_children(sh);
	return (sh->exit_status);
}
