/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 01:14:33 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/10 17:39:37 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_process_expand_loop(t_expd_cxt *ctx)
{
	while (ctx->str[*ctx->i])
	{
		if (ctx->str[*ctx->i] == '\'')
			ctx->result = ft_handle_qts(ctx->str, ctx->i,
					ctx->result, ctx->start);
		else if (ctx->str[*ctx->i] == '"')
			ctx->result = ft_handle_double_quotes(ctx);
		else if (ctx->str[*ctx->i] == '$' && ctx->str[*ctx->i + 1]
			&& (ft_isalnum(ctx->str[*ctx->i + 1])
				|| ctx->str[*ctx->i + 1] == '_'
				|| ctx->str[*ctx->i + 1] == '?'))
			ctx->result = ft_handle_dollar_sign(ctx);
		else
			(*ctx->i)++;
	}
}

char	*ft_expand_str(char *str, t_env *env, int exit)
{
	int			i;
	int			start;
	char		*result;
	t_expd_cxt	ctx;

	if (!str)
		return (NULL);
	i = 0;
	start = 0;
	result = ft_strdup("");
	ctx.str = str;
	ctx.i = &i;
	ctx.start = &start;
	ctx.result = result;
	ctx.env = env;
	ctx.exit = exit;
	ft_process_expand_loop(&ctx);
	if (i > start)
	{
		result = ft_append_part(result, str, start, i);
		ctx.result = result;
	}
	return (ctx.result);
}

static void	ft_expand_args(t_cmd *cmd, t_env *env, int exit)
{
	int		i;
	char	*expanded;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		expanded = ft_expand_str(cmd->args[i], env, exit);
		if (expanded)
		{
			free(cmd->args[i]);
			cmd->args[i] = expanded;
		}
		i++;
	}
}

static void	ft_expand_redirs(t_cmd *cmd, t_env *env, int exit)
{
	t_redir	*redir;
	char	*expanded;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->file && redir->type != redir_heredoc)
		{
			expanded = ft_expand_str(redir->file, env, exit);
			if (expanded)
			{
				free(redir->file);
				redir->file = expanded;
			}
		}
		redir = redir->next;
	}
}

void	ft_expand_variables(t_cmd *cmds, t_env *env, int exit)
{
	t_cmd	*cmd;

	cmd = cmds;
	while (cmd)
	{
		ft_expand_args(cmd, env, exit);
		ft_expand_redirs(cmd, env, exit);
		cmd = cmd->next;
	}
}
