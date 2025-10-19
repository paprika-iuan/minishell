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
	int			here;

	(void)ac;
	(void)av;
	here = 0;
	printf("%s", HEADER);
	env = envcpy(env_og);
	if (env)
		add_shlvl(env);
	//signals_nonintmode();
	while (1)
	{
		signals_intmode();
		printf("[DEBUG main] Top of loop: rl_done=%d, rl_point=%d, rl_end=%d\n",
			rl_done, rl_point, rl_end);
		input = readline(READLINE_MSG);
		if (!input)
			break ;
		add_history(input);
		tokens = tokenizer(input);
		if (!tokens)
		{
			free(input);
			continue ;
		}
		error = 0;
		ast_tree = parse_ast(tokens, &error);
		if (!ast_tree)
		{
			free_token_list(tokens);
			free(input);
			continue ;
		}
		free_token_list(tokens);
		if (error == 2)
		{
			free_ast(ast_tree);
			free(input);
			continue ;
		}
		//print_ast(ast_tree, 0);
		printf("[DEBUG main] Before handle_heredocs: rl_done=%d, rl_point=%d, rl_end=%d\n",
			rl_done, rl_point, rl_end);
		error = handle_heredocs(ast_tree, env);
		// printf("error: %i\n", error);
		signals_nonintmode();
		printf("[DEBUG main] After handle_heredocs: error=%d, g_signal=%d, rl_done=%d, rl_point=%d, rl_end=%d\n",
			error, g_signal_value, rl_done, rl_point, rl_end);
		if (error)
		{
			printf("[DEBUG main] In ERROR block, resetting readline state\n");
			rl_done = 0;
			rl_forced_update_display();
			close_all_heredocs(ast_tree);
			free_ast(ast_tree);
			free(input);
			continue ;
		}
		// if (error == ERROR)
		// {
		// 	close_all_heredocs(ast_tree);
		// 	free_ast(ast_tree);
		// 	free(input);
		// 	continue ;
		// }
		if (ast_tree->type == NODE_CMD)
			error = execute_one_command(ast_tree, env);
		else
			error = execute_ast(ast_tree, env);
		close_all_heredocs(ast_tree);
		free_ast(ast_tree);
		free(input);
		g_signal_value = 0;
	}
	rl_clear_history();
	free_env_list(env);
	//printf("%s", PITBULL);
	return (0);
}
