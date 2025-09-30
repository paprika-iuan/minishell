/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 14:41:27 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/29 19:46:40 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"


t_NodeAST	*parse_ast(t_token *tokens, int *error)
{
	t_NodeAST	*head;

	head = NULL;
	if (!tokens)
		return (NULL);
	if (head == NULL && *error == 0)
		head = set_ao_node(tokens, error);
	if (head == NULL && *error == 0)
		head = set_pipe_node(tokens, error);
	if (head == NULL && *error == 0)
		head = set_subshell_node(tokens, error);
	if (head == NULL && *error == 0)
		head = set_cmd_node(tokens, error);
	return (head);
}
//To do fora del parser:
//si parse_ast retorna null a la funcio que la crida inicialment gestionar 
// fora l'error. Hauria de tornar el prompt buit de nou. 
//Maybe fora crear una funcio per si queden tokens sense utilitzar.  
//Recorda a alliberar llistes. Proposta: alliberar t_tokens fora un cop el 
// parsing fet;