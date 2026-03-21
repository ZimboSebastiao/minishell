/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal_handlers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:45:00 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/12 20:02:53 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_signal_child(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		exit(130);
	}
	if (sig == SIGQUIT)
	{
		write(1, "Quit (core dumped)\n", 20);
		exit(131);
	}
}

void	ft_setup_child_signals(void)
{
	signal(SIGINT, ft_handle_signal_child);
	signal(SIGQUIT, ft_handle_signal_child);
}

void	ft_handle_signal_interactive(int sig)
{
	g_signal = sig;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_setup_interactive_signals(void)
{
	signal(SIGINT, ft_handle_signal_interactive);
	signal(SIGQUIT, SIG_IGN);
}
