/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:49:43 by amarquez          #+#    #+#             */
/*   Updated: 2025/09/30 11:08:56 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../inc/parser.h"

// Función para imprimir el AST (más visual)
void print_ast(t_NodeAST *node, int depth)
{
    if (!node)
        return;
    for (int i = 0; i < depth; i++) printf("  ");
    switch (node->type)
    {
        case NODE_CMD:
            printf("CMD: ");
            for (int i = 0; node->cmd.args && node->cmd.args[i]; i++)
                printf("%s ", node->cmd.args[i]);
            printf("\n");
            if (node->cmd.redirect)
                print_ast(node->cmd.redirect, depth + 1);
            break;
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

int	main(void)
{
	char		*input;
	t_token		*tokens;
	t_NodeAST	*parseado;
    int         error;

	printf("%s", HEADER);
	while (1)
	{
		input = readline(READLINE_MSG);
		if (!input)
			break ;
		add_history(input);
		tokens = tokenizer(input);
        error = 0;
		parseado = parse_ast(tokens, &error);
        if (error)
        free_token_list(tokens);
		print_ast(parseado, 0);
        printf("Error: %i\n", error);
		free(input);
		rl_clear_history();
	}
	return (0);
}
/*
		if (input_split)
		{
			if (input_split[0] && ft_strcmp(input_split[0], "echo") == 0)
				ft_echo(input_split);
			else if (input_split[0] && ft_strcmp(input_split[0], "env") == 0)
				ft_env(env_copy);
			else if (input_split[0] && ft_strcmp(input_split[0], "export") == 0)
			{
				if (input_split[1])
					ft_export(input_split + 1, &env_copy);
				else
					ft_export(NULL, &env_copy);
			}
			else if (input_split[0] && ft_strcmp(input_split[0], "unset") == 0)
			{
				if (input_split[1])
					ft_unset(input_split + 1, &env_copy);
			}
			else if (input_split[0] && ft_strcmp(input_split[0], "cd") == 0)
			{
				ft_cd(env_copy, input_split + 1);
			}
			else if (input_split[0] && ft_strcmp(input_split[0], "pwd") == 0)
			{
				ft_pwd(input_split + 1);
			}
			else if (input_split[0] && ft_strcmp(input_split[0], "exit") == 0)
			{
				ft_exit(env_copy, input_split + 1);
			}
			else if (input_split[0])
				printf("You typed: %s\n", input);
			for (int i = 0; input_split[i]; i++)
				free(input_split[i]);
			free(input_split);
		}
		free(input);
	}
	rl_clear_history();
	free_env_list(env_copy);
	return (0);
}


const char *token_type_to_string(enum token_type type)
{
    switch(type)
    {
        case AND: return "AND";
        case OR: return "OR";
        case PIPE: return "PIPE";
        case SUBSHELL: return "SUBSHELL";
        case WORD: return "WORD";
        case REDIR_IN: return "REDIR_IN";
        case REDIR_OUT_APP: return "REDIR_OUT_APP";
        case REDIR_OUT_TRUNC: return "REDIR_OUT_TRUNC";
        case REDIR_HEREDOC: return "REDIR_HEREDOC";
        default: return "UNKNOWN";
    }
}

// Function to print all tokens in a linked list
void print_tokens(t_token *head, const char *command)
{
    t_token *current = head;
    int token_count = 0;

    printf("\n=== Testing: \"%s\" ===\n", command);

    if (!current)
    {
        printf("No tokens generated (NULL returned)\n");
        return;
    }

    while (current)
    {
        printf("Token %d: [%s] \"%s\" (pos: %d)\n",
               token_count,
               token_type_to_string(current->type),
               current->content,
               current->position);
        current = current->next;
        token_count++;
    }
    printf("Total tokens: %d\n", token_count);
}

int main(void)
{
    // Test commands
    char *test_commands[] = {
        "ls -l | grep .txt",
        "echo \"hello world\" > file.txt",
        "cat < input.txt",
        "ls && echo success",
        "false || echo fallback",
        "(echo test)",
        "ls ||| wc",
        "echo 'unclosed quote",
        "var=\"hello world\"",
        "error&and",
        NULL  // Sentinel to mark end of array
    };

    printf("=== TOKENIZER TEST PROGRAM ===\n");
    printf("Testing tokenizer with various shell command patterns\n");

    // Test each command
    for (int i = 0; test_commands[i] != NULL; i++)
    {
        t_token *tokens = tokenizer(test_commands[i]);
        print_tokens(tokens, test_commands[i]);

        // Free memory for this test
        if (tokens)
            free_token_list(tokens);
    }

    printf("\n=== TEST COMPLETED ===\n");

    return 0;
}*/
