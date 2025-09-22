#include <stdio.h>
#include "env.h"

// Helper to print the env list
void print_env_list(t_env *env)
{
    printf("---- ENV LIST ----\n");
    while (env)
    {
        printf("%s\n", env->content);
        env = env->next;
    }
    printf("------------------\n");
}

// Helper to create a t_cmd list from an array of strings
t_cmd *cmd_list_from_args(char **args)
{
    t_cmd *head = NULL;
    t_cmd *current = NULL;
    int i = 0;
    while (args[i])
    {
        t_cmd *node = malloc(sizeof(t_cmd));
        node->content = ft_strdup(args[i]);
        node->next = NULL;
        if (!head)
            head = node;
        else
            current->next = node;
        current = node;
        i++;
    }
    return head;
}

// Helper to free t_cmd list
void free_cmd_list(t_cmd *cmd)
{
    t_cmd *tmp;
    while (cmd)
    {
        tmp = cmd->next;
        free(cmd->content);
        free(cmd);
        cmd = tmp;
    }
}

// Helper to free t_env list
void free_env_list(t_env *env)
{
    t_env *tmp;
    while (env)
    {
        tmp = env->next;
        free(env->content);
        free(env);
        env = tmp;
    }
}


int main(int ac, char **av, char **envp)
{
    t_env *env_list;
    
    av = NULL;
    ac = 0;
    env_list = envcpy(envp);

    // Test 1: Print initial env
    printf("Test 1: Initial env\n");
    print_env_list(env_list);

    // Test 2: Export new variable
    char *args2[] = {"VAR1=hello", NULL};
    t_cmd *cmd2 = cmd_list_from_args(args2);
    export(cmd2, &env_list);
    printf("Test 2: After export VAR1=hello\n");
    print_env_list(env_list);
    free_cmd_list(cmd2);

    // Test 3: Export duplicate variable (should update)
    char *args3[] = {"PATH=/bin", NULL};
    t_cmd *cmd3 = cmd_list_from_args(args3);
    export(cmd3, &env_list);
    printf("Test 3: After export PATH=/bin (update)\n");
    print_env_list(env_list);
    free_cmd_list(cmd3);

    // Test 4: Export invalid variable
    char *args4[] = {"1INVALID=bad", NULL};
    t_cmd *cmd4 = cmd_list_from_args(args4);
    export(cmd4, &env_list);
    printf("Test 4: After export 1INVALID=bad (should not add)\n");
    print_env_list(env_list);
    free_cmd_list(cmd4);

    // Test 5: Export multiple variables
    char *args5[] = {"VAR2=world", "VAR3=!", NULL};
    t_cmd *cmd5 = cmd_list_from_args(args5);
    export(cmd5, &env_list);
    printf("Test 5: After export VAR2=world VAR3=!\n");
    print_env_list(env_list);
    free_cmd_list(cmd5);

    // Cleanup
    free_env_list(env_list);

    return 0;
}
