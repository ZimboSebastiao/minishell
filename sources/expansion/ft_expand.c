/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 01:14:33 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/06 01:19:13 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_append_part(char *result, char *str, int start, int i)
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

char	*ft_expand_str(char *str, t_env *env, int exit_status)
{
	int		i;
	int		start;
	char	*result;

	if (!str)
		return (NULL);
	i = 0;
	start = 0;
	result = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '\'')
		{
			result = ft_append_part(result, str, start, i);
			result = ft_strjoin_free(result,
					ft_process_quotes(str, &i, '\''));
			start = i;
		}
		else if (str[i] == '"')
		{
			result = ft_append_part(result, str, start, i);
			result = ft_strjoin_free(result,
					ft_expand_double_quotes(str, &i, env, exit_status));
			start = i;
		}
		else if (str[i] == '$')
		{
			result = ft_append_part(result, str, start, i);
			result = ft_handle_dollar(str, &i, &start, result, env, exit_status);
		}
		else
			i++;
	}
	result = ft_append_part(result, str, start, i);
	return (result);
}

static void	ft_expand_args(t_cmd *cmd, t_env *env, int exit_status)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		expanded = ft_expand_str(cmd->args[i], env, exit_status);
		free(cmd->args[i]);
		cmd->args[i] = expanded;
		i++;
	}
}

static void	ft_expand_redirs(t_cmd *cmd, t_env *env, int exit_status)
{
	t_redir	*redir;
	char	*expanded;

	redir = cmd->redirs;
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
}

void	ft_expand_variables(t_cmd *cmds, t_env *env, int exit_status)
{
	t_cmd	*cmd;

	cmd = cmds;
	while (cmd)
	{
		ft_expand_args(cmd, env, exit_status);
		ft_expand_redirs(cmd, env, exit_status);
		cmd = cmd->next;
	}
}
