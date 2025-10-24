/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:49:43 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/24 12:52:14 by jgirbau-         ###   ########.fr       */
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

void	handle_c_signal(t_env *env)
{
	if (g_signal_value == SIGINT)
	{
		set_last_error(EXIT_FROM_SIGNAL + g_signal_value, env);
		g_signal_value = 0;
	}
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
		handle_c_signal(env);
		tokens = tokenizer(input, error);
		if (!no_tokens(tokens, input, error, env))
			continue ;
		ast_tree = parse_ast(tokens, error);
		free_token_list(tokens);
		if (!ast_tree && !no_ast(error, ast_tree, input, env))
			continue ;
		if (!no_heredoc(error, ast_tree, env, input))
			continue ;
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
<<<<<<< HEAD
	do_main_loop(&error, env);
=======
	while (1)
	{
		signals_intmode();
		input = readline(READLINE_MSG);
		if (!input)
			break ;
		if (!*input)
		{
			free(input);
			continue ;
		}
		add_history(input);
		if (g_signal_value == SIGINT)
		{
			set_last_error(EXIT_FROM_SIGNAL + g_signal_value, env);
			g_signal_value = 0;
		}
		tokens = tokenizer(input, &error);
		if (!tokens)
		{
			free(input);
			set_last_error(error, env);
			continue ;
		}
		ast_tree = parse_ast(tokens, &error);

		if (!ast_tree)
		{
			free_token_list(tokens);
			free(input);
			set_last_error(error, env);
			continue ;
		}
		free_token_list(tokens);
		if (error == 2)
		{
			free_ast(ast_tree);
			free(input);
			set_last_error(error, env);
			continue ;
		}
		error = handle_heredocs(ast_tree, env);
		signals_nonintmode();
		if (error)
		{
			close_all_heredocs(ast_tree);
			free_ast(ast_tree);
			free(input);
			input = NULL;
			set_last_error(error, env);
			continue ;
		}
		free(input);
		if (ast_tree->type == NODE_CMD)
			error = execute_one_command(ast_tree, env);
		else
			error = execute_ast(ast_tree, env);
		set_last_error(error, env);
		close_all_heredocs(ast_tree);
		free_ast(ast_tree);
	}
>>>>>>> 3ca03b6 (missing clean up in heredoc utils)
	rl_clear_history();
	free_env_list(env);
	return (0);
}
