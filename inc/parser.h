/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:54:16 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/29 12:04:55 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

enum e_NodeType
{
	NODE_CMD,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_REDIRECT,
	NODE_SUBSHELL,
};

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
	struct s_token *next;
}	t_token;

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
			enum token_type		type;
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

//parser.c
t_NodeAST	*parse_ast(t_token *tokens);

//parse_ao.c
t_NodeAST	*set_ao_node(t_token *token);

//parse_cmd.c
t_NodeAST	*set_cmd_node(t_token *tokens);

//parse_pipe.c
t_NodeAST	*set_pipe_node(t_token *token);

//parse_redirections.c
int 		is_redirection(int type);
t_NodeAST	*set_redirect_node(t_token *tokens);

//parse_subshell.c
int			parenthesis_close(t_token *tokens);
t_token		*set_reparse(t_token *tokens, int close);
t_NodeAST	*set_subshell_node(t_token *tokens);

//parse_utils.c
t_token	*ft_lstlast_parse(t_token *lst);
void	ft_lstadd_back_parse(t_token **lst, t_token *new);
t_token	*ft_lst_node_cpy(t_token *cpy_from);
t_token	*consume_tokens(t_token *token, int moves);

#endif