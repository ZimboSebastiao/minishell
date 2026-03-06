/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_heredoc_expand.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 14:30:00 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/06 01:49:28 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_heredoc_line(char *line, t_shell *shell)
{
	char	*expanded;

	if (!line)
		return (NULL);
	if (ft_strchr(line, '$'))
		expanded = ft_expand_str(line, shell->env_list, shell->exit_status);
	else
		expanded = ft_strdup(line);
	return (expanded);
}

static int	write_heredoc_expand(int fd, char *delimiter, t_shell *shell)
{
	char	*line;
	char	*expanded_line;

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
		expanded_line = expand_heredoc_line(line, shell);
		if (expanded_line)
		{
			write(fd, expanded_line, ft_strlen(expanded_line));
			write(fd, "\n", 1);
			free(expanded_line);
		}
		free(line);
	}
	return (0);
}

int	redir_heredoc_with_expand(t_cmd *cmd, char *delimiter, t_shell *shell)
{
	int	fd;

	fd = open(".heredoc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	write_heredoc_expand(fd, delimiter, shell);
	close(fd);
	fd = open(".heredoc_tmp", O_RDONLY);
	if (fd < 0)
		return (1);
	if (cmd->fd_in != STDIN_FILENO)
		close(cmd->fd_in);
	cmd->fd_in = fd;
	unlink(".heredoc_tmp");
	return (0);
}
