/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 01:11:43 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/06 01:11:56 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_array(char **env_array)
{
	int	i;

	i = 0;
	while (env_array && env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	if (env_array)
		free(env_array);
}

static void	exec_child_builtin(t_cmd *cmd, t_shell *sh)
{
	int	status;

	status = run_builtin(cmd, sh);
	exit(status);
}

void	child_exec(t_cmd *cmd, t_shell *sh)
{
	char	*path;
	char	**env_array;

	if (apply_redirections(cmd) != 0)
		exit(1);
	if (is_builtin(cmd->args[0]))
		exec_child_builtin(cmd, sh);
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
	exit(127);
}

int	exec_cmd(t_cmd *cmd, t_shell *sh)
{
	pid_t	pid;

	if (!cmd->next && is_builtin(cmd->args[0]))
		return (run_builtin(cmd, sh));
	pid = fork();
	if (pid == 0)
		child_exec(cmd, sh);
	else if (pid < 0)
		return (perror("fork"), 1);
	sh->last_pid = pid;
	return (0);
}
