/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 00:29:30 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/12 19:57:37 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal = 0;

// static char	**my_completion(const char *text, int start, int end)
// {
// 	(void)text;
// 	(void)start;
// 	(void)end;
// 	rl_attempted_completion_over = 1;
// 	return (NULL);
// }

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	(void)argc;
	(void)argv;
	rl_bind_key('\t', rl_complete);
	// rl_attempted_completion_function = my_completion;
	env = ft_init_env(envp);
	ft_setup_interactive_signals();
	ft_shell_loop(env);
	ft_free_env(env);
	return (0);
}
