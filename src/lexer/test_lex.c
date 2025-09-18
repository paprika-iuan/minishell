#include <stdio.h>
#include <stdlib.h>
#include "../../inc/minishell.h"

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
        token_count = count_tokens(commands[i]);
        printf("Token count: %d\n", token_count);
        tokens = lexer(commands[i]);
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
