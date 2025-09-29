/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:31:11 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/26 17:42:31 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	parenthesis_close(t_token *tokens)
{
	int		i;
	int		count; 
	t_token	*dup;

	i = 0;
	count = 0;
	dup = tokens;
	if (dup->content[0] == ')')
	{
		//set_error(should end the minishell);
		return (-1);
	}
	if (dup->content[0] == '(')
	{
		while (dup)
		{
			if (dup->content[0] == '(')
				count++;
			else if (dup->content[0] == ')')
			{
				count--;
				if (count == 0)
					return (i);
			}
			i++;
			dup = dup->next;
		}
	}
	//set_error(should end the minishell);
	return (-1);;
}

t_token	*set_reparse(t_token *tokens, int close)
{
	int		i;
	t_token	*head;
	t_token	*dup;
	t_token	*reparse;

	i = 0;
	dup = tokens;
	head = NULL;
	while (dup && i < close)
	{
		reparse = ft_lst_node_cpy(dup);
		ft_lstadd_back_parse(&head, reparse);
		dup = dup->next;
		i++;
	}
	return (head);
}

t_NodeAST	*set_subshell_node(t_token *tokens)
{
	t_NodeAST	*node;
	t_NodeAST	*redir;
	t_token		*reparse;
	t_token		*dup;
	int			close;


	close = parenthesis_close(tokens);
	if (close == -1)
	{
		//set_error(this will send it to check other operands);
		return (NULL);
	}
	node = malloc(sizeof(t_NodeAST));
	if (!node)
		return (NULL);
	node->type = NODE_SUBSHELL;
	reparse = set_reparse(tokens->next, close - 1);
	node->subshell.reparse = parse_ast(reparse);
	free_token_list(reparse);
	dup = consume_tokens(tokens, close - 1);
	dup = tokens;
	redir = set_redirect_node(dup);
	node->subshell.redirect = redir;
	return (node);
}
