/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:34:14 by amarquez          #+#    #+#             */
/*   Updated: 2025/09/11 16:34:49 by amarquez         ###   ########.fr       */
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
# define SUCCESS 1
# define FAILURE 0

# include "../libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>

/****** LEXER ******/

int is_operand(char c);
int get_operand_length(char *line);
int get_quote_length(char *line);
int get_word_length(char *line);
int	handle_quote_length(char **line, int len);
int	count_tokens(char *line);
char	*allocate_token(int size);
void	free_tokens(char **tokens, int i);
char	**lexer(char *line, int	*num_tokens);

/****** IDENTIFIER ******/

enum token_type
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
	enum token_type	type;
	char		*content;
	int			position;
	struct s_token *next;
}	t_token;

t_token	*tokenizer(char *line);
void	free_token_list(t_token *head);
t_token	*create_token(char *content);
void	free_token_list(t_token *head);
void	append_token(t_token **head, t_token **current, t_token *node);

/****** ERROR ******/

void	syntax_error(char *message);
void	basic_err(char *x);

/****** BUILTINS ******/

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
}	t_env;

int		ft_echo(char **argv);
t_env	*create_env_node(char *content);
void	add_to_env_list(t_env **cp_env, t_env *new_node);
void	free_env_list(t_env *head);
t_env	*envcpy(char **envp);
char	*get_env_value(char *key, t_env *env);
int		set_env_value(char *key, char *value, t_env *env);
int		ft_env(t_env *cp_env);
int		ft_export(char **args, t_env **cp_env);
int		ft_unset(char **args, t_env **envp);
int		ft_cd(t_env *env, char **argv);
int		ft_pwd(char **argv);
void	ft_exit(t_env *env, char **argv);

#endif
