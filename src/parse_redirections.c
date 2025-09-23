/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 14:55:02 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/21 15:22:22 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_NodeAST	*set_redirect_node(t_token **tokens, int ac)
{
	t_NodeAST	*node;

	node = malloc(sizeof(t_NodeAST));
	node->e_NodeType = NODE_REDIRECT;
	node->RedirType = type;
	node->redirect.file = what_redir(t_token **tokens, );
	node->redirect.fd = fd;
	return (node);
}
