/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:31:11 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/22 11:06:10 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// you have to figure out how to know the pos of the token. 
int	parenthesis_close(t_token *tokens)
{
	int		i;
	t_token	*dup;

	i = 0;
	dup = tokens;
	if (dup->content[0] == ')')
	{
		set_error(should end the minishell);
		return (NULL);
	}
	if (dup->content[0] == '(')
	{
		while (dup)
		{
			if (dup->content[0] == ')')
				return (i);
			i++;
			dup = dup->next;
		}
	}
	return (NULL);
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
	while (dup && i < close - 1)
	{
		reparse = ft_lst_node_cpy(dup);
		ft_lstadd_back_parse(&head, reparse);
		dup = dup->next;
		i++;
	}
	return (head);
}
// De nou, atent a les redireccions. 
// Gestiona el parenthesis error

t_NodeAST	*set_subshell_node(t_token *tokens)
{
	t_NodeAST	*node;
	int			close;

	close = parenthesis_close(tokens);
	if (!close)
	{
		set_error(this will send it to check other operands);
		return (NULL);
	}
	node = malloc(sizeof(t_NodeAST));
	if (!node)
		return (NULL);
	node->type = NODE_SUBSHELL;
	node->subshell.reparse = set_reparse(tokens, close);
	parse_ast(node->subshell.reparse);
	node->subshell.redirect = set_redirect_node(tokens, 0);
	consume_tokens(tokens, close);
	return (node);
}
