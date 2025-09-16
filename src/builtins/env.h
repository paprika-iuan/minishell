/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:21:15 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/12 12:32:59 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
}	t_env;

void	basic_err(char *x);
void	ft_lstadd_back(t_env **lst, t_env *newnode);
t_env	*ft_lstnew(void *content);
t_env	*ft_lstlast(t_env *lst);

#endif