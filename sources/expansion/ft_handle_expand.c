/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_expand.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/08 02:05:01 by zimbo             #+#    #+#             */
/*   Updated: 2026/04/09 21:41:46 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_append_part(char *result, char *str, int start, int i)
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

char	*ft_handle_qts(char *str, int *i, char *result, int *start)
{
	result = ft_append_part(result, str, *start, *i);
	result = ft_strjoin_free(result,
			ft_process_quotes(str, i, '\''));
	*start = *i;
	return (result);
}

char	*ft_handle_double_quotes(t_expd_cxt *ctx)
{
	ctx->result = ft_append_part(ctx->result, ctx->str, *ctx->start, *ctx->i);
	ctx->result = ft_strjoin_free(ctx->result,
			ft_expd_quotes(ctx->str, ctx->i,
				ctx->env, ctx->exit));
	*ctx->start = *ctx->i;
	return (ctx->result);
}

char	*ft_handle_dollar_sign(t_expd_cxt *ctx)
{
	t_dollar_data	d;

	ctx->result = ft_append_part(ctx->result, ctx->str, *ctx->start, *ctx->i);
	d.str = ctx->str;
	d.i = ctx->i;
	d.start = ctx->start;
	d.result = ctx->result;
	d.env = ctx->env;
	d.exit = ctx->exit;
	ctx->result = ft_handle_dollar(&d);
	return (ctx->result);
}

void	ft_init_cxt(t_expd_cxt *ctx, char *str,
				t_env *env, int exit)
{
	ctx->str = str;
	ctx->env = env;
	ctx->exit = exit;
}
