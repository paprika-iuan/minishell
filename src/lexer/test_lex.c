// #include <stdio.h>
// #include <stdlib.h>
// #include "../../inc/minishell.h"

/*
void print_char_array(char **arr) {
    if (!arr) return;
    for (int i = 0; arr[i] != NULL; i++) {
        const char *str = arr[i];
        printf("String %d: ", i);
        for (int j = 0; str[j] != '\0'; j++) {
            putchar(str[j]);
        }
        putchar('\n');
    }
}

char **get_commands()
{
    static char *commands[] = {
        "",
        " ",
        "pwd",
        "touch myfile.txt",
        "echo \"Hello, world!\"",
        "cd /var/log",
        "echo \"some text\" > output.txt",
        "ls -l | grep \".txt\"",
        "echo \"My username is $(whoami)\"",
        "find /var/log -name \"*.log\" -mtime -1",
        "grep -R --binary-files=without-match \"search_term\" .",
        "Hello'worl d",
        "Hello'worl d' aa",
        "Hello'world",

        // invalid ones
        "echo Hello&Worl",
        "1var=\"test\"",
        "( echo \"hello\"",
        "()",
        "ls |",
        "| grep foo",
        "ls | nope | wc -l",
        "ls non_existent | wc -l",
        "ls &&",
        "ls ||",
        "&& echo \"hi\"",
        "false || true && echo \"runs\"",
        "badcommand && echo \"success\"",
        "badcommand || echo \"fallback\"",
        "echo \"test\" > /",
        "cat < does_not_exist.txt",
        "echo \"data\" > /root/protected.txt",
        "echo \"test\" >>| file.txt",
        "ls ||| wc -l",
        "cat << EOF",
        "grep foo <<< < file.txt",
        "sleep 10 & | grep \"done\"",
        "echo \"$(echo $(echo unbalanced)\"",
        NULL
    };
    return commands;
}

void free_tokens(char **tokens)
{
    if (!tokens)
        return;

    for (int i = 0; tokens[i] != NULL; i++)
    {
        free(tokens[i]);
    }
    free(tokens);
}

int main()
{
    char **commands = get_commands();
    char **tokens;
    int token_count;

    printf("=== TOKENIZER TEST ===\n\n");
    for (int i = 0; commands[i] != NULL; i++)
    {
        printf("Command %d: \"%s\"\n", i, commands[i]);
        printf("Token count: %d\n", token_count);
        tokens = lexer(commands[i], &token_count);
        if (tokens)
        {
            printf("Tokens:\n");
            print_char_array(tokens);
            free_tokens(tokens);
        }
        else
        {
            printf("Tokenization failed!\n");
        }
        printf("----------------------------------------\n");
    }
    return 0;
}
*/
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
