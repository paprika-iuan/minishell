/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:49:43 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/24 12:02:14 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parser.h"


void	do_main_execute(t_NodeAST *ast_tree, t_env *env, int error, char *input)
{
	free(input);
	if (ast_tree->type == NODE_CMD)
		error = execute_one_command(ast_tree, env);
	else
		error = execute_ast(ast_tree, env);
	set_last_error(error, env);
	close_all_heredocs(ast_tree);
	free_ast(ast_tree);
}

int no_input(char *input)
{
	if (!*input)
	{
		free(input);
		return (0);
	}
	return (1);
}

int	no_tokens(t_token *tokens, char *input, int *error, t_env *env)
{
	if (!tokens)
	{
		free(input);
		set_last_error(*error, env);
		return (0);
	}
	return (1);
}

int no_heredoc(int *error, t_NodeAST *ast_tree, t_env *env, char *input)
{
	*error = handle_heredocs(ast_tree, env);
	signals_nonintmode();
	if (*error)
	{
		close_all_heredocs(ast_tree);
		free_ast(ast_tree);
		free(input);
		input = NULL;
		set_last_error(*error, env);
		return (0);
	}
	return (1);
}

int	no_ast(int *error, t_NodeAST *ast_tree, char *input, t_env *env)
{
	if (*error)
	{
		free_ast(ast_tree);
		free(input);
		set_last_error(*error, env);
		return (0);
	}
	return (1);
}

void	do_main_loop(int *error, t_env *env)
{
	t_token		*tokens;
	char		*input;
	t_NodeAST	*ast_tree;
	
	while (1)
	{
		signals_intmode();
		input = readline(READLINE_MSG);
		if (!input)
			break ;
		if (!no_input(input))
			continue ;
		add_history(input);
		tokens = tokenizer(input, error);
		if (!no_tokens(tokens, input, error, env))
			continue ;
		ast_tree = parse_ast(tokens, error);
		free_token_list(tokens);
		if (!ast_tree && !no_ast(error, ast_tree, input, env))
			continue ;
		if (!no_heredoc(error, ast_tree, env, input))
			continue;
		do_main_execute(ast_tree, env, *error, input);
	}
}

int	main(int ac, char **av, char **env_og)
{
	t_env		*env;
	int			error;

	(void)ac;
	(void)av;
	printf("%s", HEADER);
	env = envcpy(env_og);
	if (env)
		add_shlvl(env);
	error = 0;
	set_last_error(error, env);
	do_main_loop(&error, env);
	rl_clear_history();
	free_env_list(env);
	return (0);
}
