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

void	do_main_execute(t_NodeAST *ast_tree, t_mini *mini, int error, char *input)
{
	free(input);
	if (ast_tree->type == NODE_CMD)
		error = execute_one_command(ast_tree, mini);
	else
		error = execute_ast(ast_tree, mini);
	set_last_error(error, mini);
	close_all_heredocs(ast_tree);
	free_ast(ast_tree);
}

void	handle_c_signal(t_mini *mini)
{
	t_env	*env;

	env = mini->env;
	if (g_signal_value == SIGINT)
	{
		set_last_error(EXIT_FROM_SIGNAL + g_signal_value, mini);
		g_signal_value = 0;
	}
}

void	do_main_loop(int *error, t_mini *mini)
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
		handle_c_signal(mini);
		tokens = tokenizer(input, error);
		if (!no_tokens(tokens, input, error, mini))
			continue ;
		ast_tree = parse_ast(tokens, error);
		free_token_list(tokens);
		if (*error && !no_ast(error, ast_tree, input, mini))
			continue ;
		if (!no_heredoc(error, ast_tree, mini, input))
			continue ;
		do_main_execute(ast_tree, mini, *error, input);
	}
}

int	main(int ac, char **av, char **env_og)
{
	t_mini		mini;
	int			error;

	(void)ac;
	(void)av;
	printf("%s", HEADER);
	mini.env = envcpy(env_og);
	if (mini.env)
		add_shlvl(mini.env);
	mini.last_error = 0;
	error = 0;
	set_last_error(error, &mini);
	do_main_loop(&error, &mini);
	rl_clear_history();
	free_env_list(mini.env);
	return (0);
}
