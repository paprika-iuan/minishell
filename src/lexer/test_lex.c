#include <stdio.h>

void print_char_array(char **arr) {
    if (!arr) return; // Null-check

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
        "pwd",
        "touch myfile.txt",
        "echo \"Hello, world!\"",
        "cd /var/log",
        "echo \"some text\" > output.txt",
        "ls -l | grep \".txt\"",
        "echo \"My username is $(whoami)\"",
        "find /var/log -name \"*.log\" -mtime -1",
        "grep -R --binary-files=without-match \"search_term\" .",

        // invalid ones
        "echo \"Hello Worl",
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
