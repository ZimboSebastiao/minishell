/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 22:52:07 by zimbo             #+#    #+#             */
/*   Updated: 2026/02/16 04:27:02 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;
void	ft_free_tokens(t_token *list)
{
	t_token	*tmp;
	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->value);
		free(tmp);
	}
}

void	ft_shell_loop(t_env *env)
{
	char	*line;
	t_token	*tokens;
	t_cmd	*cmds;
	t_shell	shell;

	shell.env_list = env;
	shell.exit_status = 0;
	while (1)
	{
		line = readline("minishell> ");
		if (!line)
		{
			printf("exit\n");
			break;
		}
		if (*line)
			add_history(line);
		tokens = ft_lexer(line);
		if (tokens)
		{
			cmds = ft_parser(tokens);
			if (cmds)
			{
				shell.cmds = cmds;
				(void)shell;
				// ft_expand_variables(cmds, env, shell.exit_status);
				// ft_executor(&shell);
				ft_free_cmds(cmds);
			}
			ft_free_tokens(tokens);
		}

		free(line);
	}
}
