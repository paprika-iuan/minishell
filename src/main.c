/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:49:43 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/10 10:26:11 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parser.h"

void print_ast(t_NodeAST *node, int depth)
{
    if (!node)
        return;
    for (int i = 0; i < depth; i++) printf("  ");
    switch (node->type)
    {
        case NODE_CMD:
        {
            int argc = 0;
            printf("CMD: ");
            for (int i = 0; node->cmd.args && node->cmd.args[i]; i++) {
                //printf("%s ", node->cmd.args[i]);
                argc++;
            }
            printf("(argc: %d)\n", node->cmd.ac);
            if (node->cmd.redirect)
                print_ast(node->cmd.redirect, depth + 1);
            break;
        }
        case NODE_PIPE:
            printf("PIPE\n");
            print_ast(node->binary.left, depth + 1);
            print_ast(node->binary.right, depth + 1);
            break;
        case NODE_AND:
            printf("AND\n");
            print_ast(node->binary.left, depth + 1);
            print_ast(node->binary.right, depth + 1);
            break;
        case NODE_OR:
            printf("OR\n");
            print_ast(node->binary.left, depth + 1);
            print_ast(node->binary.right, depth + 1);
            break;
        case NODE_SUBSHELL:
            printf("SUBSHELL\n");
            print_ast(node->subshell.reparse, depth + 1);
            if (node->subshell.redirect)
                print_ast(node->subshell.redirect, depth + 1);
            break;
        case NODE_REDIRECT:
            printf("REDIRECT: type=%d file=%s\n", node->redirect.type, node->redirect.file);
            if (node->redirect.redirect)
                print_ast(node->redirect.redirect, depth + 1);
            break;
        default:
            printf("UNKNOWN NODE\n");
    }
}

int	main(int ac, char **av, char **env_og)
{
	char		*input;
	t_token		*tokens;
	t_NodeAST	*ast_tree;
	t_env		*env;
	int			error;

	printf("%s", HEADER);
	env = envcpy(env_og);
	while (1)
	{
        signals_intmode();
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
			// printf("Parse error: %i\n", error);
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
		if (ast_tree->type == NODE_CMD)
			error = execute_one_command(ast_tree, env);
		else
			error = execute_ast(ast_tree, env);
		free_ast(ast_tree);
		free(input);
	}
    rl_clear_history();
    free_env_list(env);
    //printf("%s", PITBULL);
	return (0);
}
