/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:34:14 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/24 16:13:55 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define HEADER "\033[1;36m\
███████╗ ██████╗ ██╗   ██╗     ██████╗ ██████╗ ███╗   ██╗ ██████╗██╗  ██╗ █████╗        ███████╗███╗   ██╗████████╗██████╗  ██████╗ \n\
██╔════╝██╔═══██╗╚██╗ ██╔╝    ██╔════╝██╔═══██╗████╗  ██║██╔════╝██║  ██║██╔══██╗       ██╔════╝████╗  ██║╚══██╔══╝██╔══██╗██╔═══██╗\n\
███████╗██║   ██║ ╚████╔╝     ██║     ██║   ██║██╔██╗ ██║██║     ███████║███████║       █████╗  ██╔██╗ ██║   ██║   ██████╔╝██║   ██║\n\
╚════██║██║   ██║  ╚██╔╝      ██║     ██║   ██║██║╚██╗██║██║     ██╔══██║██╔══██║       ██╔══╝  ██║╚██╗██║   ██║   ██╔══██╗██║   ██║\n\
███████║╚██████╔╝   ██║       ╚██████╗╚██████╔╝██║ ╚████║╚██████╗██║  ██║██║  ██║▄█╗    ███████╗██║ ╚████║   ██║   ██║  ██║╚██████╔╝\n\
╚══════╝ ╚═════╝    ╚═╝        ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝    ╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝ \n\
\033[0m"

# define READLINE_MSG "\033[1;31m[🏓wanghao]\033[35m$> \033[0m"
# define READLINE_HEREDOC "\033[1;34mheredoc> \033[0m"
# define SUCCESS 1
# define FAILURE 0
# define COMMAND_NOT_EXECUTABLE 126
# define COMMAND_NOT_FOUND 127
# define EXIT_FROM_SIGNAL 128
# define FORK_SUCCESS 0
# define FORK_FAILED -1
# define WAITPID_FAILED -2
# define MALLOC_FAILED -3
# define ERROR 1
# define UNCLOSED_QUOTES -42

# include "../libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <signal.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>

extern int	g_signal_value;

/****** LEXER ******/

int		is_operand(char c);
int		get_operand_length(char *line);
int		get_quote_length(char *line);
int		get_word_length(char *line);
int		handle_quote_length(char **line, int len);
int		count_tokens(char *line);
char	*allocate_token(int size);
void	free_tokens(char **tokens, int i);
char	**lexer(char *line, int	*num_tokens, int *error);

/****** IDENTIFIER ******/

enum	e_token_type
{
	AND,
	OR,
	PIPE,
	SUBSHELL,
	WORD,
	REDIR_IN,
	REDIR_OUT_APP,
	REDIR_OUT_TRUNC,
	REDIR_HEREDOC
};

typedef struct s_token
{
	enum e_token_type	type;
	char				*content;
	struct s_token		*next;
}	t_token;

t_token	*tokenizer(char *line, int *error);
void	free_token_list(t_token *head);
t_token	*create_token(char *content);
void	append_token(t_token **head, t_token **current, t_token *node);

/****** BUILTINS ******/

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
}	t_env;

t_env	*create_env_node(char *content);
void	add_to_env_list(t_env *env, t_env *new_node);
void	free_env_list(t_env *head);
t_env	*envcpy(char **envp);
void	add_shlvl(t_env *env);
char	*get_env_value(char *key, t_env *env);
int		set_env_value(char *key, char *value, t_env *env);
int		ft_echo(char **args);
int		ft_env(char **args, t_env *env);
int		ft_export(char **args, t_env *env);
int		ft_unset(char **args, t_env **env_ref);
int		ft_cd(char **args, t_env *env);
int		ft_pwd(char **args, t_env *env);
int		env_list_size(t_env *env);

/****** EXECUTOR ******/

typedef struct s_pipe_struct
{
	int		num_pipes;
	int		*pipes;
	int		pipe_idx;
	pid_t	pid;
	pid_t	*child_pids;
}	t_pipe_struct;

/****** SIGNALS.C ******/

void	sig_int_c(int sign);
void	signals_intmode(void);
void	signals_nonintmode(void);
void	setup_heresignals(int *exit_from_signal);
void	set_heresign(int sign);

/****** ERROR.C ******/

void	set_last_error(int error, t_env *env);
int		get_last_error(t_env *env);

#endif
