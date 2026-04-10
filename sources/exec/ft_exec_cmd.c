/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 21:36:01 by zimbo             #+#    #+#             */
/*   Updated: 2026/04/09 21:36:04 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env_array(char **env_array)
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

static void	ft_exec_child_builtin(t_cmd *cmd, t_shell *sh)
{
	int	status;

	status = ft_run_builtin(cmd, sh);
	exit(status);
}

void	ft_child_exec(t_cmd *cmd, t_shell *sh)
{
	char	*path;
	char	**env_array;

	ft_setup_child_signals();
	if (!cmd->args || !cmd->args[0])
	{
		if (ft_apply_redirections(cmd, sh) != 0)
			exit(1);
		exit(0);
	}
	if (ft_apply_redirections(cmd, sh) != 0)
		exit(1);
	if (ft_is_builtin(cmd->args[0]))
		ft_exec_child_builtin(cmd, sh);
	path = ft_resolve_path(cmd->args[0], sh->env_list);
	if (!path)
	{
		ft_put_error("command not found: ", cmd->args[0], NULL);
		write(1, "\n", 1);
		exit(127);
	}
	env_array = ft_env_to_array(sh->env_list);
	execve(path, cmd->args, env_array);
	perror("minishell");
	free(path);
	ft_free_env_array(env_array);
	exit(127);
}

int	ft_exec_cmd(t_cmd *cmd, t_shell *sh)
{
	pid_t	pid;

	if (!cmd->args || !cmd->args[0])
		return (0);
	if (!cmd->next && ft_is_builtin(cmd->args[0]))
		return (ft_run_builtin(cmd, sh));
	pid = fork();
	if (pid == 0)
		ft_child_exec(cmd, sh);
	else if (pid < 0)
		return (perror("fork"), 1);
	sh->last_pid = pid;
	return (0);
}
