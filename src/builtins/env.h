/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:21:15 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/16 11:26:22 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct s_env
{
	char			*content;
	struct s_env	*next;
}	t_env;

typedef struct s_cmd
{
	char			*content;
	struct s_cmd	*next;
}	t_cmd;

void	basic_err(char *x);
void	ft_lstadd_back(t_env **lst, t_env *newnode);
t_env	*ft_lstnew(void *content);
t_env	*ft_lstlast(t_env *lst);
void	ft_lstdelone(t_env *lst, void (*del)(void *));

int	unset(t_cmd **token, t_env **envp);
int	env(t_env *cp_env);
int	export(t_cmd *token, t_env **cp_env);
t_env	*envcpy(char **envp);

//test_utils
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *str);
char	*ft_strchr(const char *s, int c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_isalpha(int c);
int	ft_isalnum(int c);
int	ft_isdigit(int c);



#endif