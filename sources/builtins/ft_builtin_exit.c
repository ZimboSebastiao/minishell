/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ft_builtin_exit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 15:30:00 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/12 21:12:03 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_is_numeric(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_builtin_exit(char **argv, t_shell *shell)
{
	int	status;

	if (argv[1] && !ft_is_numeric(argv[1]))
	{
		ft_put_error("exit: ", argv[1],
			": numeric argument required\n");
		shell->exit = 2;
		return (2);
	}
	if (argv[1] && argv[2])
	{
		ft_put_error("exit: ", NULL,
			"too many arguments\n");
		shell->exit = 1;
		return (1);
	}
	printf("exit\n");
	if (argv[1])
	{
		status = ft_atoi(argv[1]);
		exit(status);
	}
	exit(shell->exit);
}
