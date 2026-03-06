/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 01:12:09 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/06 01:12:13 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	resolve_cmd(t_cmd *c, t_shell *sh)
{
	char	*path;

	if (is_builtin(c->args[0]))
		return (1);
	path = resolve_path(c->args[0], sh->env_list);
	if (!path)
	{
		ft_put_error(c->args[0], NULL, "command not found");
		sh->exit_status = 127;
		return (0);
	}
	free(path);
	return (1);
}

static void	close_fds(t_cmd *cmd, int pipe_fd[2], int prev_pipe)
{
	if (cmd->fd_in != STDIN_FILENO && cmd->fd_in != prev_pipe)
		close(cmd->fd_in);
	if (cmd->has_pipe)
		close(pipe_fd[1]);
	if (cmd->fd_out != STDOUT_FILENO && !cmd->has_pipe)
		close(cmd->fd_out);
	if (prev_pipe != -1)
		close(prev_pipe);
}

static void	fork_and_exec(t_cmd *cmd, t_shell *sh, int cmd_ok)
{
	sh->last_pid = fork();
	if (sh->last_pid == 0)
	{
		if (!cmd_ok)
			exit(127);
		child_exec(cmd, sh);
	}
}

static int	exec_single_builtin(t_cmd *cmd, t_shell *sh, int cmd_ok)
{
	if (!cmd_ok)
		return (1);
	sh->exit_status = run_builtin(cmd, sh);
	return (0);
}

int	executor(t_cmd *list, t_shell *sh)
{
	t_cmd	*tmp;
	int		p[2];
	int		prev_pipe;
	int		cmd_ok;

	prev_pipe = -1;
	tmp = list;
	while (tmp)
	{
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
		close_fds(tmp, p, prev_pipe);
		if (tmp->next)
			prev_pipe = p[0];
		tmp = tmp->next;
	}
	wait_children(sh);
	return (sh->exit_status);
}
