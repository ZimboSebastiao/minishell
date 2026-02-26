/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:05:57 by zimbo             #+#    #+#             */
/*   Updated: 2026/02/26 00:07:26 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_h
# define MINISHELL_h

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../lib/libft1/libft.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

extern int g_signal;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,		// <
	TOKEN_REDIR_OUT,	// >
	TOKEN_HEREDOC,		// <<
	TOKEN_APPEND		// >>
}	t_token_type;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}	t_redir_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct	s_token	*next;
}	t_token;

typedef struct s_redir
{
	t_redir_type		type;
	char				*file;
	struct s_redir		*next;
}	t_redir;

typedef struct s_cmd
{
	char			**args;
	t_redir			*redirs;
	struct s_cmd	*next;
}	t_cmd;

typedef	struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct	s_shell
{
	t_env	*env_list;
	t_cmd	*cmds;
	int		exit_status;
	int		stdin_backup;
	int		stdout_backup;
}	t_shell;

/* Loop principal */
void	ft_shell_loop(t_env *env);
void	ft_handle_signal(int sig);

/* Tokenização */
t_token	*ft_new_token(t_token_type type, char *value);
void	ft_add_token(t_token **list, t_token *new);
t_token	*ft_read_operator(char **line);
void	ft_free_tokens(t_token *list);
void	ft_skip_spaces(char **line);
t_token	*ft_read_word(char **line);
t_token	*ft_lexer(char *input);
int		ft_is_operator(char	c);

/* Parsing */
t_redir	*ft_new_redir(t_redir_type type, char *file);
void	ft_add_redir(t_redir **list, t_redir *new);
void	ft_add_cmd(t_cmd **list, t_cmd *new);
t_cmd	*ft_parser(t_token *tokens);
t_cmd	*ft_new_cmd(void);

/* Expansão */
void	ft_expand_variables(t_cmd *cmds, t_env *env, int exit_status);
char	*ft_expand_str(char *str, t_env *env, int exit_status);
char	*ft_get_env_value(char *key, t_env *env);

/* Ambiente */
void	ft_set_env(char *key, char *value, t_env **env);
t_env	*ft_init_env(char	**envp);
void	ft_unset_env(char *key, t_env **env);
char	*ft_get_env(char *key, t_env *env);
char	**ft_env_to_array(t_env *env);
void	ft_free_env(t_env *env);

/* Utilitários */
void	ft_put_error(char *s1, char *s2, char *s3);
void	ft_free_redirs(t_redir *redirs);
void	ft_free_cmds(t_cmd *cmds);


#endif