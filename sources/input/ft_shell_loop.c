/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 22:52:07 by zimbo             #+#    #+#             */
/*   Updated: 2026/02/16 02:43:08 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tokens(t_token *list)
{
	t_token	*tmp.
	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp->value);
		free(tmp);
	}
}

void	ft_free_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	ft_shell_loop(void)
{
	char	*line;
	char	**args;
	int		status;

	status = 1;
	while (status)
	{
		line = readline("> ");
		if (!line)
		{
			printf("\n");
			break;
		}
		if (*line)
			add_history(line);
		args = ft_lexer(line);
		status = ft_executor(args);

		free(line);
		ft_free_args(args);
	}
}
