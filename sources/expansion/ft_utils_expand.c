/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 01:13:58 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/08 03:23:00 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*append_before_dollar(t_dollar_data *d)
{
	char	*temp;
	char	*new_result;

	if (*d->i > *d->start)
	{
		temp = ft_strndup(d->str + *d->start, *d->i - *d->start);
		new_result = ft_strjoin(d->result, temp);
		free(d->result);
		free(temp);
		d->result = new_result;
	}
	return (d->result);
}

static char	*expand_and_append_var(t_dollar_data *d)
{
	char	*var_name;
	char	*var_value;
	char	*new_result;

	var_name = ft_get_var_name(d->str, d->i);
	var_value = ft_get_var_value(var_name, d->env, d->exit);
	free(var_name);
	new_result = ft_strjoin(d->result, var_value);
	free(d->result);
	free(var_value);
	d->result = new_result;
	*d->start = *d->i;
	return (d->result);
}

char	*ft_handle_dollar(t_dollar_data *d)
{
	d->result = append_before_dollar(d);
	d->result = expand_and_append_var(d);
	return (d->result);
}

static char	*append_remaining_text(char *str, int start, int i, char *result)
{
	char	*temp;
	char	*new_result;

	if (i > start)
	{
		temp = ft_strndup(str + start, i - start);
		new_result = ft_strjoin(result, temp);
		free(result);
		free(temp);
		result = new_result;
	}
	return (result);
}

char	*ft_expd_quotes(char *str, int *i, t_env *env, int exit)
{
	int		start;
	char	*result;

	(*i)++;
	start = *i;
	result = ft_strdup("");
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
			result = ft_handle_dollar(&(t_dollar_data){str, i,
					&start, result, env, exit});
		else
			(*i)++;
	}
	result = append_remaining_text(str, start, *i, result);
	if (str[*i] == '"')
		(*i)++;
	return (result);
}
