/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 03:20:11 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/10 15:59:54 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_args(t_token *start)
{
	int		count;
	t_token	*temp;

	count = 0;
	temp = start;
	while (temp && temp->type != TOKEN_PIPE)
	{
		if (temp->type == TOKEN_WORD)
			count++;
		temp = temp->next;
	}
	return (count);
}

static char	**ft_alloc_args(int count)
{
	char	**args;

	args = ft_calloc(count + 1, sizeof(char *));
	return (args);
}

static void	ft_parse_redirection(t_token **current, t_cmd *cmd)
{
	t_redir	*redir;

	if ((*current)->next && (*current)->next->type == TOKEN_WORD)
	{
		redir = ft_new_redir(
				ft_token_to_redir((*current)->type),
				ft_strdup((*current)->next->value)
				);
		ft_add_redir(&cmd->redirs, redir);
		*current = (*current)->next;
	}
}

static int	ft_fill_cmd_args(t_token **current, t_cmd *cmd, int arg_count)
{
	char	**args;
	int		i;

	args = ft_alloc_args(arg_count);
	if (!args)
		return (1);
	i = 0;
	while (*current && (*current)->type != TOKEN_PIPE)
	{
		if ((*current)->type == TOKEN_WORD)
		{
			args[i] = ft_strdup((*current)->value);
			i++;
		}
		else if ((*current)->type >= TOKEN_REDIR_IN)
			ft_parse_redirection(current, cmd);
		*current = (*current)->next;
	}
	cmd->args = args;
	return (0);
}

t_cmd	*ft_parser(t_token *tokens)
{
	t_cmd	*cmds;
	t_cmd	*current_cmd;
	t_token	*current;
	int		arg_count;

	cmds = NULL;
	current = tokens;
	while (current)
	{
		current_cmd = ft_new_cmd();
		if (!current_cmd)
			return (NULL);
		arg_count = ft_count_args(current);
		if (ft_fill_cmd_args(&current, current_cmd, arg_count) != 0)
			return (NULL);
		ft_add_cmd(&cmds, current_cmd);
		if (current && current->type == TOKEN_PIPE)
			current = current->next;
	}
	return (cmds);
}
