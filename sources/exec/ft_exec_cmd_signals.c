/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft_exec_cmd_signals.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:50:00 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/12 19:37:49 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_ft_child_exec_with_signals(t_cmd *cmd, t_shell *sh)
{
	char	*path;
	char	**env_array;

	ft_setup_child_signals();
	if (ft_apply_redirections(cmd, sh) != 0)
		exit(1);
	if (ft_is_builtin(cmd->args[0]))
	{
		sh->exit = ft_run_builtin(cmd, sh);
		exit(sh->exit);
	}
	path = ft_resolve_path(cmd->args[0], sh->env_list);
	if (!path)
	{
		ft_put_error(cmd->args[0], NULL, "command not found\n");
		exit(127);
	}
	env_array = ft_env_to_array(sh->env_list);
	execve(path, cmd->args, env_array);
	perror("minishell");
	free(path);
	ft_free_env_array(env_array);
	exit(126);
}
