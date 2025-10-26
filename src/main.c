/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:49:43 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/24 16:36:33 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parser.h"

void	do_main_execute(t_NodeAST *ast_tree, t_env **env_ref, \
	int error, char *input)
{
	free(input);
	if (ast_tree->type == NODE_CMD)
		error = execute_one_command(ast_tree, env_ref);
	else
		error = execute_ast(ast_tree, env_ref);
	set_last_error(error, *env_ref);
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

void	do_main_loop(int *error, t_env **env_ref)
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
		handle_c_signal(*env_ref);
		tokens = tokenizer(input, error);
		if (!no_tokens(tokens, input, error, *env_ref))
			continue ;
		ast_tree = parse_ast(tokens, error);
		free_token_list(tokens);
		if (*error && !no_ast(error, ast_tree, input, env))
			continue ;
		if (!no_heredoc(error, ast_tree, *env_ref, input))
			continue ;
		do_main_execute(ast_tree, env_ref, *error, input);
	}
}

int	main(int ac, char **av, char **env_og)
{
	t_env		**env_ref;
	t_env		*env;
	int			error;

	(void)ac;
	(void)av;
	printf("%s", HEADER);
	env = envcpy(env_og);
	env_ref = &env;
	if (env)
		add_shlvl(env);
	error = 0;
	set_last_error(error, env);
<<<<<<< HEAD
	do_main_loop(&error, env_ref);
=======
	do_main_loop(&error, env);
>>>>>>> 07bb994 (heredoc quote removal and norminette done)
	rl_clear_history();
	free_env_list(env);
	return (0);
}
