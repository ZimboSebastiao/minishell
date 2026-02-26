/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 23:05:00 by zimbo             #+#    #+#             */
/*   Updated: 2026/02/26 00:16:46 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_var_name(char *str, int *i)
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
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '-'))
		(*i)++;
	var_name = ft_strndup(str + start, *i - start);
	return (var_name);
}

static char	*ft_get_var_value(char *var_name, t_env *env, int exit_status)
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

static char	*ft_process_quotes(char *str, int *i, char quote)
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

static char	*ft_expand_single_quotes(char *str, int *i)
{
	return (ft_process_quotes(str, i, '\''));
}

static char	*ft_expand_double_quotes(char *str, int *i, t_env *env, int exit_status)
{
	char	*new_result;
	char	*var_value;
	char	*var_name;
	char	*result;
	char	*temp;
	int		start;

	(*i)++;
	start = *i;
	result = ft_strdup("");
	while (str[*i] && str[*i] != '"')
	{
		if (str[*i] == '$')
		{
			if (*i > start)
			{
				temp = ft_strndup(str + start, *i - start);
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
			start = *i;
		}
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

char	*ft_expand_str(char *str, t_env *env, int exit_status)
{
	int		i;
	int		start;
	char	*result;
	char	*temp;
	char	*var_name;
	char	*var_value;
	char	*new_result;

	if (!str)
		return (NULL);
	i = 0;
	start = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\'')
		{
			if (i > start)
			{
				temp = ft_strndup(str + start, i - start);
				new_result = ft_strjoin(result, temp);
				free(result);
				free(temp);
				result = new_result;
			}
			temp = ft_expand_single_quotes(str, &i);
			new_result = ft_strjoin(result, temp);
			free(result);
			free(temp);
			result = new_result;
			start = i;
		}
		else if (str[i] == '"')
		{
			if (i > start)
			{
				temp = ft_strndup(str + start, i - start);
				new_result = ft_strjoin(result, temp);
				free(result);
				free(temp);
				result = new_result;
			}
			temp = ft_expand_double_quotes(str, &i, env, exit_status);
			new_result = ft_strjoin(result, temp);
			free(result);
			free(temp);
			result = new_result;
			start = i;
		}
		else if (str[i] == '$')
		{
			if (i > start)
			{
				temp = ft_strndup(str + start, i - start);
				new_result = ft_strjoin(result, temp);
				free(result);
				free(temp);
				result = new_result;
			}
			var_name = ft_get_var_name(str, &i);
			var_value = ft_get_var_value(var_name, env, exit_status);
			free(var_name);
			new_result = ft_strjoin(result, var_value);
			free(result);
			free(var_value);
			result = new_result;
		}
		else
			i++;
	}
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

void	ft_expand_variables(t_cmd *cmds, t_env *env, int exit_status)
{
	char	*expanded;
	t_cmd	*cmd;
	int		i;

	cmd = cmds;
	while (cmd)
	{
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			expanded = ft_expand_str(cmd->args[i], env, exit_status);
			free(cmd->args[i]);
			cmd->args[i] = expanded;
			i++;
		}
		t_redir	*redir = cmd->redirs;
		while (redir)
		{
			if (redir->file && redir->type != REDIR_HEREDOC)
			{
				expanded = ft_expand_str(redir->file, env, exit_status);
				free(redir->file);
				redir->file = expanded;
			}
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}