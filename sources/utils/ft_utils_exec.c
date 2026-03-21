/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 01:06:42 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/08 02:55:07 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_resolve_cmd(t_cmd *c, t_shell *sh)
{
	char	*path;

	if (ft_is_builtin(c->args[0]))
		return (1);
	path = ft_resolve_path(c->args[0], sh->env_list);
	if (!path)
	{
		ft_put_error(c->args[0], NULL, "command not found\n");
		sh->exit = 127;
		return (0);
	}
	free(path);
	return (1);
}

void	ft_close_fds(t_cmd *cmd, int pipe_fd[2], int prev_pipe)
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

void	ft_fork_and_exec(t_cmd *cmd, t_shell *sh, int cmd_ok)
{
	sh->last_pid = fork();
	if (sh->last_pid == 0)
	{
		if (!cmd_ok)
			exit(127);
		ft_child_exec(cmd, sh);
	}
}
