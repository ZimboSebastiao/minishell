/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 21:31:28 by zimbo             #+#    #+#             */
/*   Updated: 2026/05/09 20:07:11 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int  ft_write_heredoc(int fd, char *delimiter)
{
    char    *line;

    while (1)
    {
        line = readline("heredoc> ");
        if (!line)
        {
            rl_cleanup_after_signal();
            break ;
        }
        if (g_signal == SIGINT)
        {
            free(line);
            rl_cleanup_after_signal();
            break ;
        }
        if (ft_strcmp(line, delimiter) == 0)
        {
            free(line);
            break ;
        }
        write(fd, line, ft_strlen(line));
        write(fd, "\n", 1);
        free(line);
    }
    return (0);
}

static void ft_handle_signal_heredoc(int sig)
{
    g_signal = sig;
    if (sig == SIGINT)
    {
        write(1, "\n", 1);
        rl_done = 1;
    }
}

static int  ft_create_heredoc_file(char *delimiter)
{
    int fd;

    fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd < 0)
        return (-1);
    g_signal = 0;
    signal(SIGINT, ft_handle_signal_heredoc);
    ft_write_heredoc(fd, delimiter);
    signal(SIGINT, SIG_IGN);
    close(fd);
    if (g_signal == SIGINT)
    {
        unlink(".heredoc_tmp");
        return (-1);
    }
    fd = open(".heredoc_tmp", O_RDONLY);
    if (fd < 0)
        return (-1);
    unlink(".heredoc_tmp");
    return (fd);
}

int	ft_redir_heredoc(t_cmd *cmd, char *delimiter)
{
	int	fd;

	fd = ft_create_heredoc_file(delimiter);
	if (fd < 0)
		return (1);
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	cmd->fd_in = fd;
	return (0);
}
