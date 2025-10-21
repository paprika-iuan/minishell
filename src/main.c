/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:49:43 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/03 13:01:01 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parser.h"

int	main(int ac, char **av, char **env_og)
{
	char		*input;
	t_token		*tokens;
	t_NodeAST	*ast_tree;
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
	//printf("%i\n", get_last_error(env));
	while (1)
	{
		signals_intmode();
		input = readline(READLINE_MSG);
		if (!input)
			break ;
		add_history(input);
		error = 0;
		tokens = tokenizer(input, &error);
		printf("====error: %i===\n", error);
		if (!tokens)
		{
			free(input);
			set_last_error(error, env);
			printf("===last error: %i===\n", get_last_error(env));
			continue ;
		}
		ast_tree = parse_ast(tokens, &error);
		//printf("%i\n", error);
		set_last_error(error, env);
		if (!ast_tree)
		{
			free_token_list(tokens);
			free(input);
			printf("===last error: %i===\n", get_last_error(env));
			continue ;
		}
		free_token_list(tokens);
		if (error == 2)
		{
			free_ast(ast_tree);
			free(input);
			printf("===last error: %i===\n", get_last_error(env));
			continue ;
		}
		//print_ast(ast_tree, 0);
		error = handle_heredocs(ast_tree, env);

		signals_nonintmode();
		if (error)
		{
			close_all_heredocs(ast_tree);
			free_ast(ast_tree);
			free(input);
			input = NULL;
			set_last_error(error, env);
			printf("===last error: %i===\n", get_last_error(env));
			continue ;
		}
		free(input);
		if (ast_tree->type == NODE_CMD)
			error = execute_one_command(ast_tree, env);
		else
			error = execute_ast(ast_tree, env);
		set_last_error(error, env);
		printf("===last error: %i===\n", get_last_error(env));
		close_all_heredocs(ast_tree);
		free_ast(ast_tree);
	}
	rl_clear_history();
	free_env_list(env);
	return (0);
}
