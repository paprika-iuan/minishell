/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:49:10 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/15 18:11:03 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void	del_token(t_cmd *token, t_env **envp)
{
	t_env	*current;
	t_env	*prev;
	int		len;

	current = *envp;
	prev = NULL;
	len = ft_strlen(token->content);
	while (current)
	{
		if (!ft_strncmp((token)->content, current->content, len) && (
				current->content[len] == '=' || current->content[len] == '\0'))
		{
			if (prev)
				prev->next = current->next;
			else
				*envp = current->next;
			ft_lstdelone(current);
			break;
		}
		prev = current;
		current = current->next;
	}
}

int	unset(t_cmd **token, t_env **envp)
{
	t_cmd	*cp_token;
	if (!(*token) || !(*envp))
		return (1);
	cp_token = *token;
	while (cp_token)
	{
		del_token(cp_token, envp);
		cp_token = cp_token->next;
	}
	return (0);
}
