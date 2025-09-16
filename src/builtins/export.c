/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:48:07 by jgirbau-          #+#    #+#             */
/*   Updated: 2025/09/15 17:42:37 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//adds quotes when printing export.

void	var_printer(t_env *current)
{
	char	*eq;

	while (current)
	{
		eq = ft_strchr(current->content, '=');
		if (eq)
		{
			write(1, "declare -x ", 12);
			write(1, current->content, eq - current->content);
			write(1, "=\"");
			write(1, eq + 1, ft_strlen(eq + 1));
			write(1, "\"\n", 2);
		}
		else
			printf("declare -x %s\n", current->content);
		current = current->next;
	}
}

//checks that the var declaration is crrect.

int	export_arg_checker(char *args)
{
	int	i;

	i = 0;
	if (!ft_isalpha(args[0]) || args[0] != '_')
	{
		perror(export: (printf("%s:", args)) invalid option);
		return (0);
	}
	while (args[i] && args[i] != '=')
	{
		else if (!ft_isalnum(args[i]) || args[i] != '_')
		{
			perror(export: (printf("%s:", args)) not a valid identifier);
			return (0);
		}
		i++;
	}
	return (1);
}

//Falta fer un merge amb les llistes del parsing. Hauria de rebre cada args 
// com a token per separat, per tant, en el else tan sols hauria de iterar 
// entre nodes, no ha de fer cas a espais.

t_env	dup_var_handler(t_cmd *token, t_env *cp_env)
{
	int		len;
	t_env	iter;

	len = 0;
	while (token->content && token->content[len++] != '=')
		;
	iter = cp_env;
	while (iter)
	{
		if (!ft_strncmp(token->content, iter->content, len))
		{
			free(iter->content);
			iter->content = strdup(token->content);
			return (iter);
		}
		iter = iter->next;
	}
	return (ft_lstnew(token->content));
}

int	dup_checker(t_env *cp_env, t_env *new_node)
{
	t_env	iter;
	int		a;

	iter = cp_env;
	while (iter)
	{
		a = ft_strcmp(iter, new_node);
		if (a)
			iter = iter->next;
		else
			return (0);
	}
	return (1);
}

int	export(t_cmd *token, t_env **cp_env)
{
	t_env	*new_node;
	t_env	*current;
	int		i;

	i = 0;
	if (!token->content)
	{
		current = *cp_env;
		var_printer(current);
		return (0);
	}
	while (token->content)
	{
		if (export_arg_checker(token->content))
		{
			new_node = dup_var_handler(token, *cp_env);
			basic_err(new_node);
			if (dup_checker(cp_env, new_node))
				ft_lstadd_back(*cp_env, new_node);
		}
		token = token->next;
	}
	return (0);
}
//Evitar duplicados: No comprueba si la variable ya existe antes de añadirla.
//Validación: No valida si el argumento es un nombre de variable válido.