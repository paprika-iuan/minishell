/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ao.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 17:37:40 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/22 11:52:46 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ao_location(t_token *tokens)
{
	int		i;
	t_token	*dup;

	i = 0;
	dup = tokens;
	while (dup)
	{
		if (dup->type == AND || dup->type == OR)
			return (i);
		i++;
		dup = dup->next;
	}
	return (NULL);
}
void	node_type_setter(t_token *token, t_NodeAST *node)
{
	if (toke->type == AND)
		node->type = NODE_AND;
	if (toke->type == AND)
		node->type = NODE_AND;
}

t_NodeAST	*set_ao_node(t_token *token)
{
	t_NodeAST	*node;
	t_token		*dup;
	t_token		*left;
	int			operand;

	if (!token)
		return (NULL);
	operand = ao_location(token);
	dup = token;
	
	node = malloc(sizeof(t_NodeAST));
	if (!node)
		return (NULL);
	node_type_setter(token, node);
	node->binary.left = parse_ast(left);
	if (!ft_strcmp(dup->content, '||', 2) || !ft_strcmp(dup->content, '&&', 2))
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
