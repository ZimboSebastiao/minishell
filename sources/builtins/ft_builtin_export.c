/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin_export.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 21:44:19 by zimbo             #+#    #+#             */
/*   Updated: 2026/04/09 21:44:21 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_export_var(char *arg, t_shell *shell)
{
	char	*equal_sign;
	char	*key;
	char	*value;
	char	*arg_copy;

	equal_sign = ft_strchr(arg, '=');
	if (!equal_sign)
		return (1);
	arg_copy = ft_strdup(arg);
	if (!arg_copy)
		return (1);
	equal_sign = ft_strchr(arg_copy, '=');
	*equal_sign = '\0';
	key = arg_copy;
	value = equal_sign + 1;
	ft_set_env(key, value, &shell->env_list);
	free(arg_copy);
	return (0);
}

int	ft_builtin_export(char **argv, t_shell *shell)
{
	int		i;
	t_env	*tmp;

	if (!argv[1])
	{
		tmp = shell->env_list;
		while (tmp)
		{
			if (tmp->value)
				printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
			else
				printf("declare -x %s\n", tmp->key);
			tmp = tmp->next;
		}
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		ft_export_var(argv[i], shell);
		i++;
	}
	return (0);
}
