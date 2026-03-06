/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 01:13:58 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/06 01:19:38 by zimbo            ###   ########.fr       */
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

char	*ft_get_var_value(char *var_name, t_env *env, int exit_status)
{
	char	*value;

	if (ft_strcmp(var_name, "?") == 0)
		value = ft_itoa(exit_status);
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

char	*ft_handle_dollar(char *str, int *i, int *start,
			char *result, t_env *env, int exit_status)
{
	char	*var_name;
	char	*var_value;
	char	*new_result;
	char	*temp;

	if (*i > *start)
	{
		temp = ft_strndup(str + *start, *i - *start);
		new_result = ft_strjoin(result, temp);
		free(result);
		free(temp);
		result = new_result;
	}
	var_name = ft_get_var_name(str, i);
	var_value = ft_get_var_value(var_name, env, exit_status);
	free(var_name);
	new_result = ft_strjoin(result, var_value);
	free(result);
	free(var_value);
	result = new_result;
	*start = *i;
	return (result);
}

char	*ft_expand_double_quotes(char *str, int *i, t_env *env, int exit_status)
{
	int		start;
	char	*result;
	char	*new_result;
	char	*temp;

	(*i)++;
	start = *i;
	result = ft_strdup("");
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
			result = ft_handle_dollar(str, i, &start, result, env, exit_status);
		else
			(*i)++;
	}
	if (*i > start)
	{
		temp = ft_strndup(str + start, *i - start);
		new_result = ft_strjoin(result, temp);
		free(result);
		free(temp);
		result = new_result;
	}
	if (str[*i] == '"')
		(*i)++;
	return (result);
}
