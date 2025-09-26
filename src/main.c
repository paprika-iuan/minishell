/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:49:43 by amarquez          #+#    #+#             */
/*   Updated: 2025/09/12 10:49:45 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*input;
	char	**input_split;
	t_env	*env_copy;
	char *tmp;
	char *pwd;
	char *prompt;

	env_copy = envcpy(envp);
	if (!env_copy)
	{
		perror("Error: Failed to copy environment\n");
		return (1);
	}

	printf("%s", HEADER);
	while (1)
	{
		pwd = get_env_value("PWD", env_copy);
		if (!pwd)
			pwd = "";
		tmp = ft_strjoin(READLINE_MSG, "\033[1;36m");
		prompt = ft_strjoin(tmp, pwd);
		free(tmp);
		tmp = ft_strjoin(prompt, "\033[0m ");
		free(prompt);
		prompt = tmp;
		input = readline(prompt);
		free(prompt);
		if (!input)
			break ;
		add_history(input);
		input_split = ft_split(input, ' ');
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

/*
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
}
*/
