/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:54:16 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/21 15:56:04 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

enum
{
	NODE_CMD,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_REDIR,
	NODE_SUBSHELL,
}	e_NodeType;

enum
{
	APPEND,
	HERE_DOC,
	APPEND,
	CONCAT,
}	e_RedirType;

typedef struct s_NodeAST
{
	e_NodeType	type;
	union
	{
		struct s_cmd
		{
			char			**args;
			int				ac;
			struct NodeAST	*redirect;
		}	cmd;
		struct s_binary
		{
			struct NodeAST	*left;
			struct NodeAST	*right;
		}	binary;
		struct s_redirect
		{
			RedirType	*type;
			char		*file;
			int			fd;
		}	redirect;
		struct s_subshell
		{
			t_token			**reparse;
			struct NodeAST	*redirect;
		}	subshell;
	};
}	t_NodeAST;