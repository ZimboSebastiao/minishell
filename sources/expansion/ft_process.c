/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 02:23:21 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/08 02:55:07 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_var_name(char *str, int *i)
{
	int		start;
	char	*var_name;

	(*i)++;
	start = *i;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_strdup("?"));
	}
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var_name = ft_strndup(str + start, *i - start);
	return (var_name);
}

char	*ft_get_var_value(char *var_name, t_env *env, int exit)
{
	char	*value;

	if (ft_strcmp(var_name, "?") == 0)
		value = ft_itoa(exit);
	else
	{
		value = ft_get_env(var_name, env);
		if (value)
			value = ft_strdup(value);
		else
			value = ft_strdup("");
	}
	return (value);
}

char	*ft_process_quotes(char *str, int *i, char quote)
{
	int		start;
	char	*result;

	(*i)++;
	start = *i;
	while (str[*i] && str[*i] != quote)
		(*i)++;
	result = ft_strndup(str + start, *i - start);
	if (str[*i] == quote)
		(*i)++;
	return (result);
}
