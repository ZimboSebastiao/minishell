/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:00:00 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/06 01:09:34 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cmd_not_found_status(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == -1)
			return (127);
		if (access(cmd, X_OK) == -1)
			return (126);
	}
	return (127);
}

int	get_permission_denied_status(char *cmd)
{
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == -1)
			return (126);
	}
	return (1);
}

void	set_exit_from_signal(int sig, t_shell *shell)
{
	if (sig == SIGINT)
		shell->exit = 130;
	else if (sig == SIGQUIT)
		shell->exit = 131;
	else
		shell->exit = 128 + sig;
}

int	get_redir_error_status(void)
{
	return (1);
}
