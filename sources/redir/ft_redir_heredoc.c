/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir_heredoc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 21:31:28 by zimbo             #+#    #+#             */
/*   Updated: 2026/04/09 21:31:31 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_write_heredoc(int fd, char *delimiter)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
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

static int	ft_create_heredoc_file(char *delimiter)
{
	int	fd;

	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (-1);
	ft_write_heredoc(fd, delimiter);
	close(fd);
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
