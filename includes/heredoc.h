/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 15:10:00 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/06 00:53:32 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEREDOC_H
# define HEREDOC_H

typedef struct s_cmd	t_cmd;
typedef struct s_shell	t_shell;

typedef struct s_heredoc_info
{
	char	*delimiter;
	int		expand;
}	t_heredoc_info;

t_heredoc_info	*parse_heredoc_delimiter(char *delimiter_token);
int				redir_heredoc_with_expand(t_cmd *cmd, char *delimiter,
					t_shell *shell);
int				redir_heredoc_noexpand(t_cmd *cmd, char *delimiter);

#endif