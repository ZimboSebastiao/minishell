/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 15:30:00 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/06 00:57:07 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_exit_status(char **argv, t_shell *shell)
{
	if (argv[1])
		return (ft_atoi(argv[1]));
	return (shell->exit_status);
}

int	builtin_exit(char **argv, t_shell *shell)
{
	int	status;

	status = get_exit_status(argv, shell);
	printf("exit\n");
	exit(status);
}
