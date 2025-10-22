/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:35:26 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/10/05 12:54:09 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../inc/parser.h"

int	count_words(t_token *tokens, int ac)
{
	t_token	*dup;
	int		i;
	int		count;

	i = 0;
	count = 0;
	dup = tokens;
	while (dup && i < ac)
	{
		if (is_redirection(dup->type))
		{
			if (dup->next && dup->next->type == WORD)
				dup = dup->next;
			else if (!dup->next)
				return (0);
		}
		else if (dup->type == WORD)
			count++;
		dup = dup->next;
		i++;
	}
	return (count);
}

t_token	*cmd_args_loop(t_token *dup, int *i, char **args, int *j)
{
	if (is_redirection(dup->type))
	{
		while (dup && is_redirection(dup->type))
		{
			dup = dup->next;
			(*i)++;
		}
		if (dup && dup->type == WORD)
		{
			dup = dup->next;
		}
	}
	else if (dup && dup->type == WORD)
	{
		args[(*j)++] = ft_strndup(dup->content, ft_strlen(dup->content));
		dup = dup->next;
	}
	return (dup);
}

char	**cmd_args(t_token *tokens, int ac)
{
	char	**args;
	int		i;
	int		j;
	int		count;
	t_token	*dup;

	i = 0;
	j = 0;
	dup = tokens;
	count = count_words(tokens, ac);
	if (!count)
		return (NULL);
	args = malloc(sizeof(char *) * (count + 1));
	if (!args)
		return (NULL);
	while (dup && i < ac)
	{
		dup = cmd_args_loop(dup, &i, args, &j);
		i++;
	}
	args[count] = NULL;
	return (args);
}

t_NodeAST	*set_cmd_node(t_token *tokens, int *error)
{
	t_NodeAST	*node;
	t_token		*dup;
	t_NodeAST	*redir;
	char		**args;
	int			ac;

	dup = tokens;
	ac = count_tokens_cmd(tokens);
	if (!ac)
		return (NULL);
	node = malloc(sizeof(t_NodeAST));
	if (!node)
		return (NULL);
	node->type = NODE_CMD;
	args = cmd_args(tokens, ac);
	if (!args)
		node->cmd.args = NULL;
	else
		node->cmd.args = args;
	node->cmd.ac = count_words(tokens, ac);
	if (is_subshell(dup, error))
		return (NULL);
	redir = set_redirect_node(dup, error);
	node->cmd.redirect = redir;
	return (node);
}
