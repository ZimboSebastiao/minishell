/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 15:30:00 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/06 00:56:48 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_set_pwd(t_shell *shell, char *old, char *new)
{
	ft_set_env("OLDPWD", old, &shell->env_list);
	ft_set_env("PWD", new, &shell->env_list);
	return (0);
}

static int	cd_to_home(t_shell *shell)
{
	char	*home_value;

	home_value = ft_get_env("HOME", shell->env_list);
	if (!home_value)
	{
		ft_put_error("cd", NULL, "HOME not set");
		return (1);
	}
	if (chdir(home_value) != 0)
		return (perror("cd"), 1);
	return (0);
}

int	builtin_cd(char **argv, t_shell *shell)
{
	char	old[4096];
	char	new[4096];

	getcwd(old, 4096);
	if (!argv[1])
	{
		if (cd_to_home(shell) != 0)
			return (1);
	}
	else
	{
		if (chdir(argv[1]) != 0)
			return (perror("cd"), 1);
	}
	getcwd(new, 4096);
	return (cd_set_pwd(shell, old, new));
}
