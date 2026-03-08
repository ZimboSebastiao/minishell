/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zimbo <zimbo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/24 19:05:57 by zimbo             #+#    #+#             */
/*   Updated: 2026/03/08 02:58:03 by zimbo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "../lib/libft1/libft.h"
# include "heredoc.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

extern int						g_signal;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_HEREDOC,
	TOKEN_APPEND
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
	t_token_type		type;
	char				*value;
	struct s_token		*next;
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
	int				fd_in;
	int				fd_out;
	int				has_pipe;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	t_env	*env_list;
	t_cmd	*cmds;
	int		exit;
	int		stdin_backup;
	int		stdout_backup;
	int		last_pid;
}	t_shell;

typedef struct s_dollar_data
{
	char	*str;
	int		*i;
	int		*start;
	char	*result;
	t_env	*env;
	int		exit;
}	t_dollar_data;

typedef struct s_quote_data
{
	char	*str;
	int		*i;
	char	quote;
}	t_quote_data;

typedef struct s_expand_context
{
	char	*str;
	int		*i;
	char	*result;
	int		*start;
	t_env	*env;
	int		exit;
}	t_expd_cxt;

/* Heredoc */
typedef struct s_heredoc_info	t_heredoc_info;

int				ft_handle(t_cmd *cmd, char *delimiter_token, t_shell *shell);

/* Loop principal */
void			ft_shell_loop(t_env *env);
void			ft_handle_signal(int sig);

/* Tokenização */
t_token			*handle_redirection(char **line, char current);
t_token			*ft_new_token(t_token_type type, char *value);
void			ft_add_token(t_token **list, t_token *new);
t_token			*ft_read_operator(char **line);
void			ft_free_tokens(t_token *list);
void			ft_skip_spaces(char **line);
t_token			*ft_read_word(char **line);
t_token			*ft_lexer(char *input);
int				ft_is_operator(char c);

/* Parsing */
t_redir_type	ft_token_to_redir(t_token_type type);
t_redir			*ft_new_redir(t_redir_type type, char *file);
void			ft_add_redir(t_redir **list, t_redir *new);
void			ft_add_cmd(t_cmd **list, t_cmd *new);
t_cmd			*ft_parser(t_token *tokens);
t_cmd			*ft_new_cmd(void);

/* Expansão */
char			*ft_get_var_name(char *str, int *i);
char			*ft_get_var_value(char *var_name, t_env *env, int exit);
char			*ft_process_quotes(char *str, int *i, char quote);
char			*ft_append_part(char *result, char *str, int start, int i);
char			*ft_handle_qts(char *str, int *i, char *result, int *start);
char			*handle_double_quotes(t_expd_cxt *ctx);
char			*handle_dollar_sign(t_expd_cxt *ctx);
void			ft_init_cxt(t_expd_cxt *ctx, char *str, t_env *env, int exit);
char			*ft_handle_dollar(t_dollar_data *d);
void			ft_expand_variables(t_cmd *cmds, t_env *env, int exit);
char			*ft_expd_quotes(char *str, int *i, t_env *env, int exit);
char			*ft_expand_str(char *str, t_env *env, int exit);
char			*ft_get_env_value(char *key, t_env *env);

/* Ambiente  */
t_env			*ft_init_env(char **envp);
char			*ft_get_env(char *key, t_env *env);
void			ft_set_env(char *key, char *value, t_env **env);
void			ft_unset_env(char *key, t_env **env);
char			*join_key_value(t_env *env);
int				count_env_vars(t_env *env);
char			**ft_env_to_array(t_env *env);
void			ft_parse_env_var(char *env_var, char **key, char **value);
void			ft_add_env_node(t_env **env, t_env *new);
t_env			*ft_new_env_node(char *key, char *value);
void			ft_free_env(t_env *env);

/* Ambiente */
int				ft_env_size(char **env);
int				env_index(char **env, char *key);
char			**env_add(char **env, char *new_var);
char			**env_remove(char **env, char *key);

/* Builtins */
int				is_builtin(char *cmd);
int				run_builtin(t_cmd *cmd, t_shell *shell);
int				builtin_echo(char **argv);
int				builtin_cd(char **argv, t_shell *shell);
int				builtin_pwd(void);
int				builtin_env(t_shell *shell);
int				builtin_export(char **argv, t_shell *shell);
int				builtin_unset(char **argv, t_shell *shell);
int				builtin_exit(char **argv, t_shell *shell);

/* Execução */
int				executor(t_cmd *list, t_shell *sh);
int				exec_cmd(t_cmd *cmd, t_shell *sh);
void			child_exec(t_cmd *cmd, t_shell *sh);
char			*resolve_path(char *cmd, t_env *env);
void			wait_children(t_shell *shell);
void			update_exit(int status, t_shell *shell);
int				resolve_cmd(t_cmd *c, t_shell *sh);
void			close_fds(t_cmd *cmd, int pipe_fd[2], int prev_pipe);
void			fork_and_exec(t_cmd *cmd, t_shell *sh, int cmd_ok);

/* Redirecionamentos */
int				setup_pipe(t_cmd *cmd, int pipe_fd[2]);
int				redir_input(t_cmd *cmd, char *file);
int				redir_output(t_cmd *cmd, char *file);
int				redir_append(t_cmd *cmd, char *file);
int				redir_heredoc(t_cmd *cmd, char *delimiter);
int				apply_redirections(t_cmd *cmd);

/* Utilitários */
void			ft_put_error(char *s1, char *s2, char *s3);
void			ft_free_redirs(t_redir *redirs);
void			ft_free_cmds(t_cmd *cmds);
void			free_split(char **split);
char			*ft_strjoin_free(char *s1, char *s2);
void			free_env_array(char **env_array);

/* Signal handling */
void			setup_child_signals(void);
void			setup_interactive_signals(void);
void			handle_signal_child(int sig);
void			child_exec_with_signals(t_cmd *cmd, t_shell *sh);

/* Error handling */
void			cleanup_fds(t_cmd *cmd);
int				handle_redir_error(t_cmd *cmd, char *file, int error_code);
int				check_file_access(char *file, int mode);
int				get_cmd_not_found_status(char *cmd);
int				get_permission_denied_status(char *cmd);
void			set_exit_from_signal(int sig, t_shell *shell);
int				get_redir_error_status(void);
int				validate_cmd(t_cmd *cmd, t_shell *sh);

#endif