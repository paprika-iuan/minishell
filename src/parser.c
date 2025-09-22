/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:41:27 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/21 16:14:50 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Recorda a gestionar els tokens sobrants a set_error
//si token encara te valor, error;
//Recorda a alliberar llistes. Proposta: alliberar t_tokens a linia 34 o fora
//un cop el parsing fet;
t_NodeAST	parse_ast(t_token *tokens)
{
	t_NodeAST	*head;

	head = NULL;
	if (head == NULL)
		head = set_ao_node(tokens);
	else if (head == NULL)
		head = set_pipe_node(tokens);
	else if (head == NULL)
		head = set_subshell_node(tokens);
	else if (head == NULL)
		head = set_cmd_node(tokens);
	else if (head == NULL)
	{
		set_error();
		return (1);
	}
	return (head);
}
