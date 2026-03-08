/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd_signals.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:50:00 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/08 02:55:07 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_child_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	child_exec_with_signals(t_cmd *cmd, t_shell *sh)
{
	char	*path;
	char	**env_array;

	if (apply_redirections(cmd) != 0)
		exit(1);
	if (is_builtin(cmd->args[0]))
	{
		sh->exit = run_builtin(cmd, sh);
		exit(sh->exit);
	}
	handle_child_signals();
	path = resolve_path(cmd->args[0], sh->env_list);
	if (!path)
	{
		ft_put_error(cmd->args[0], NULL, "command not found");
		exit(127);
	}
	env_array = ft_env_to_array(sh->env_list);
	execve(path, cmd->args, env_array);
	perror("minishell");
	free(path);
	free_env_array(env_array);
	exit(126);
}
