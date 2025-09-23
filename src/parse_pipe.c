/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 15:35:22 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/21 15:59:00 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_NodeAST	*set_pipe_node(t_token *tokens)
{
	t_NodeAST	*node;
	t_token		*dup;

	dup = token;
	node = malloc(sizeof(t_NodeAST));
	if (!node)
		return (NULL);
	node->type = NODE_PIPE;
	node->binary.left = parse_ast(dup);
	if (dup->content[0] == '|')
		dup = dup->next;
	else
	{
		set_error(should search for other operands);
		return (NULL);
	}
	node->binary.right = parse_ast(dup);
	if (node->binary.right)
		token = dup;
	return (node);
}
