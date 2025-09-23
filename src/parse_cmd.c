/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:35:26 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/21 15:59:07 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//L'hauras de refer amb les redireccions. Fuck 'em.

int	count_words(t_token *tokens)
{
	int		count;
	t_token	*dup;

	count = 0;
	dup = tokens;
	while (dup)
	{
		dup = dup->next;
		count++;
	}
	if (!count)
	{
		set_error(No queden tokens o simplement no nhi han);
		return (0);
	}
	return (count);
}

char	**cmd_args(t_token *tokens, int ac)
{
	char	**args;
	int		i;
	t_token	*dup;

	i = 0;
	dup = tokens;
	args = malloc(sizeof(char *) * (ac + 1));
	if (!args)
		return (NULL);
	if (!tokens)
	{
		set_error(No queden tokens o simplement no nhi han);
		return (NULL);
	}
	while (i < ac)
	{
		args[i] = ft_strdup(dup->content);
		dup = dup->next;
		i++;
	}
	args[ac] = NULL;
	return (args);
}

//chequeja les redireccions. Pinta percal.
t_NodeAST	*set_cmd_node(t_token *tokens)
{
	t_NodeAST	*node;
	int			ac;

	ac = count_words(tokens);
	if (!ac || !tokens)
	{
		set_error(No queden tokens o simplement no nhi han);
		return (NULL);
	}
	node = malloc(sizeof(t_NodeAST));
	if (!node)
		return (NULL);
	node->type = NODE_CMD;
	node->cmd.ac = ac;
	node->cmd.args = cmd_args(tokens, ac);
	if (tokens->type == REDIRECT)
		node->cmd.redirect = set_redirect_node(tokens, ac);
	//Calcular i sumar quants tokens NOMES SET REDIRECT avansa.
	//Si OK avansa tokens i despres cmd avansa els ac.
	else
		node->cmd.redirect = NULL;
	consume_tokens(tokens, ac);
	return (node);
}
