/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:54:16 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/24 16:35:51 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# define SYNTAX_ERROR "wanghao: syntax error near unexpected token\n"
# include "minishell.h"

enum e_NodeType
{
	NODE_CMD,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_REDIRECT,
	NODE_SUBSHELL,
};

typedef struct s_NodeAST
{
	enum e_NodeType	type;
	union
	{
		struct s_cmd
		{
			char				**args;
			int					ac;
			struct s_NodeAST	*redirect;
		}	cmd;
		struct s_binary
		{
			struct s_NodeAST	*left;
			struct s_NodeAST	*right;
		}	binary;
		struct s_redirect
		{
			enum e_token_type	type;
			char				*file;
			int					fd;
			struct s_NodeAST	*redirect;
		}	redirect;
		struct s_subshell
		{
			struct s_NodeAST	*reparse;
			struct s_NodeAST	*redirect;
		}	subshell;
	};
}	t_NodeAST;

/****** PARSER.C ******/

t_NodeAST	*parse_ast(t_token *tokens, int *error);
void		free_ast(t_NodeAST *head);

/****** PARSE_AO.C ******/

t_NodeAST	*set_ao_node(t_token *token, int *error);
int			operand_error(int i, t_token *dup, int *error);

/****** PARSE_CMD.C ******/

t_NodeAST	*set_cmd_node(t_token *tokens, int *error);

/****** PARSE_PIPE.C ******/

t_NodeAST	*set_pipe_node(t_token *token, int *error);
int			is_right_empty(t_token *dup, int *error);
void		free_left_set_right(t_token *left, t_token **right, int operand);

/****** PARSE_REDIRECTIONS.C ******/

int			is_redirection(int type);
t_NodeAST	*set_redirect_node(t_token *tokens, int *error);

/****** PARSE_SUBSHELL.C ******/

int			parenthesis_close(t_token *tokens);
t_token		*set_reparse(t_token *tokens, int close, int *error);
t_NodeAST	*set_subshell_node(t_token *tokens, int *error);
int			is_subshell(t_token *dup, int *error);

/****** PARSE_UTILS.C ******/

t_token		*ft_lstlast_parse(t_token *lst);
void		ft_lstadd_back_parse(t_token **lst, t_token *new);
t_token		*ft_lst_node_cpy(t_token *cpy_from);
t_token		*consume_tokens(t_token *token, int moves);
int			count_tokens_cmd(t_token *tokens);

/****** EXECUTOR ******/

int			execute_ast(t_NodeAST *node, t_env **env_ref);
int			execute_and_or(t_NodeAST *node, t_env **env_ref);
int			execute_pipe_sequence(t_NodeAST *node, t_env *env);
int			execute_subshell(t_NodeAST *node, t_env *env);
int			execute_command(t_NodeAST *node, t_env **env_ref);
int			execute_cmd(t_NodeAST *node, t_env *env);
int			set_pipes(t_pipe_struct *t_pipe, t_NodeAST *node);
void		close_pipes(t_pipe_struct *t_pipe);
int			allocate_child_pids(t_pipe_struct *t_pipe);
int			wait_for_children(t_pipe_struct *t_pipe);
void		cleanup_child(char *full_path, char **env_arr);
char		*set_cmd_path(t_NodeAST *node, t_env *env);
int			execute_one_command(t_NodeAST *node, t_env **env_ref);
int			is_builtin(t_NodeAST *node);
int			execute_builtin(t_NodeAST *node, t_env **env_ref);
void		update_node_args(t_NodeAST *node, t_env *env);

/****** BUILTINS ******/

int			ft_exit(char **args, t_env *env, t_NodeAST *node);

/****** REDIRECTIONS ******/

int			open_files(t_NodeAST *node);
int			do_redirections(t_NodeAST *node, t_env *env);
int			has_infile(t_NodeAST *node);
int			has_outfile(t_NodeAST *node);
int			open_file(t_NodeAST *node);
int			exec_builtin_with_redirections(t_NodeAST *node, t_env *env);
void		setup_pipe_cmd_fds(t_pipe_struct *t_pipe, t_NodeAST *node);
int			pipe_node_redirections(t_NodeAST *node, t_env *env);
int			has_quotes(char *str);
char		*remove_quotes(char *str);

/****** HEREDOC ******/

void		print_file_error(char *filename);
int			handle_heredocs(t_NodeAST *node, t_env *env);
int			read_heredoc_input(int tmp_file, char *delimitter, t_env *env);
char		*make_here_name(int id);
void		close_all_heredocs(t_NodeAST *node);

/****** ERROR_MAIN.C ******/
int			no_input(char *input);
int			no_tokens(t_token *tokens, char *input, int *error, t_env *env);
int			no_heredoc(int *error, t_NodeAST *ast_tree, t_env *env, char *input);
int			no_ast(int *error, t_NodeAST *ast_tree, char *input, t_env *env);

#endif
