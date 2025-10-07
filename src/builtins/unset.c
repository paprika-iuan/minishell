/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/15 15:49:10 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/16 10:51:14 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	del_token(char *token_content, t_env **envp)
{
	t_env	*current;
	t_env	*prev;
	int		len;

	current = *envp;
	prev = NULL;
	len = ft_strlen(token_content);
	while (current)
	{
		if (!ft_strncmp(token_content, current->content, len) && (
				current->content[len] == '=' || current->content[len] == '\0'))
		{
			if (prev)
				prev->next = current->next;
			else
				*envp = current->next;
			free(current->content);
			free(current);
			break ;
		}
		prev = current;
		current = current->next;
	}
}

int	ft_unset(char **args, t_env **envp)
{
	int	i;

	if (!args || !(*envp))
		return (1);
	i = 1;
	while (args[i])
	{
		del_token(args[i], envp);
		i++;
	}
	return (0);
}
