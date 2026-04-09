/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft_run_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 15:30:00 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/08 02:55:07 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_exec_builtin_cmd(t_cmd *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->args[0], "echo") == 0)
		return (ft_builtin_echo(cmd->args));
	if (ft_strcmp(cmd->args[0], "cd") == 0)
		return (ft_builtin_cd(cmd->args, shell));
	if (ft_strcmp(cmd->args[0], "pwd") == 0)
		return (ft_builtin_pwd());
	if (ft_strcmp(cmd->args[0], "env") == 0)
		return (ft_builtin_env(shell));
	if (ft_strcmp(cmd->args[0], "export") == 0)
		return (ft_builtin_export(cmd->args, shell));
	if (ft_strcmp(cmd->args[0], "unset") == 0)
		return (ft_builtin_unset(cmd->args, shell));
	if (ft_strcmp(cmd->args[0], "exit") == 0)
		return (ft_builtin_exit(cmd->args, shell));
	return (1);
}

static int	ft_save_std_fds(int *save_stdin, int *save_stdout)
{
	*save_stdin = dup(STDIN_FILENO);
	*save_stdout = dup(STDOUT_FILENO);
	if (*save_stdin < 0 || *save_stdout < 0)
		return (1);
	return (0);
}

static void	ft_restore_std_fds(int save_stdin, int save_stdout)
{
	dup2(save_stdin, STDIN_FILENO);
	dup2(save_stdout, STDOUT_FILENO);
	close(save_stdin);
	close(save_stdout);
}

int	ft_run_builtin(t_cmd *cmd, t_shell *shell)
{
	int	status;
	int	save_stdin;
	int	save_stdout;

	if (ft_save_std_fds(&save_stdin, &save_stdout) != 0)
		return (1);
	if (ft_apply_redirections(cmd, shell) != 0)
	{
		ft_restore_std_fds(save_stdin, save_stdout);
		shell->exit = 1;
		return (1);
	}
	shell->stdin_backup = save_stdin;
	shell->stdout_backup = save_stdout;
	status = ft_exec_builtin_cmd(cmd, shell);
	shell->stdin_backup = -1;
	shell->stdout_backup = -1;
	ft_restore_std_fds(save_stdin, save_stdout);
	shell->exit = status;
	return (status);
}