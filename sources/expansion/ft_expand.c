/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 01:14:33 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/08 03:06:25 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_expand_loop(t_expd_cxt *ctx, int *i,
				int *start, char *str)
{
	while (str[*i])
	{
		if (str[*i] == '\'')
			ctx->result = ft_handle_qts(str, i, ctx->result, start);
		else if (str[*i] == '"')
			ctx->result = handle_double_quotes(ctx);
		else if (str[*i] == '$')
			ctx->result = handle_dollar_sign(ctx);
		else
			(*i)++;
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
	ft_init_cxt(&ctx, str, env, exit);
	ctx.result = result;
	ctx.i = &i;
	ctx.start = &start;
	process_expand_loop(&ctx, &i, &start, str);
	ctx.result = ft_append_part(ctx.result, str, start, i);
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
		free(cmd->args[i]);
		cmd->args[i] = expanded;
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
		if (redir->file && redir->type != REDIR_HEREDOC)
		{
			expanded = ft_expand_str(redir->file, env, exit);
			free(redir->file);
			redir->file = expanded;
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
