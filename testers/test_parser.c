#include "../inc/parser.h"

// Helpers para crear tokens manualmente
t_token *new_token(char *content, int type)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return NULL;
    token->content = content;
    token->type = type;
    token->next = NULL;
    return token;
}

// void append_token(t_token **head, t_token *new)
// {
//     t_token *tmp = *head;
//     if (!tmp)
//         *head = new;
//     else
//     {
//         while (tmp->next)
//             tmp = tmp->next;
//         tmp->next = new;
//     }
// }

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

// Test cases
// int main(void)
// {

//     printf("Caso 1: echo hola\n");
//     t_token *tokens1 = NULL;
//     append_token(&tokens1, new_token("echo", WORD));
//     append_token(&tokens1, new_token("hola", WORD));
//     t_NodeAST *ast1 = parse_ast(tokens1);
//     print_ast(ast1, 0);

//     printf("\nCaso 2: echo hola | grep h\n");
//     t_token *tokens2 = NULL;
//     append_token(&tokens2, new_token("echo", WORD));
//     append_token(&tokens2, new_token("hola", WORD));
//     append_token(&tokens2, new_token("|", PIPE));
//     append_token(&tokens2, new_token("grep", WORD));
//     append_token(&tokens2, new_token("h", WORD));
//     t_NodeAST *ast2 = parse_ast(tokens2);
//     print_ast(ast2, 0);

//     printf("\nCaso 3: echo hola && ls\n");
//     t_token *tokens3 = NULL;
//     append_token(&tokens3, new_token("echo", WORD));
//     append_token(&tokens3, new_token("hola", WORD));
//     append_token(&tokens3, new_token("&&", AND));
//     append_token(&tokens3, new_token("ls", WORD));
//     t_NodeAST *ast3 = parse_ast(tokens3);
//     print_ast(ast3, 0);

//     printf("\nCaso 4: (echo hola && ls) | grep h\n");
//     t_token *tokens4 = NULL;
//     append_token(&tokens4, new_token("(", SUBSHELL));
//     append_token(&tokens4, new_token("echo", WORD));
//     append_token(&tokens4, new_token("hola", WORD));
//     append_token(&tokens4, new_token("&&", AND));
//     append_token(&tokens4, new_token("ls", WORD));
//     append_token(&tokens4, new_token(")", SUBSHELL));
//     append_token(&tokens4, new_token("|", PIPE));
//     append_token(&tokens4, new_token("grep", WORD));
//     append_token(&tokens4, new_token("h", WORD));
//     t_NodeAST *ast4 = parse_ast(tokens4);
//     print_ast(ast4, 0);

//     printf("\nCaso 5: echo hola > outfile\n");
//     t_token *tokens5 = NULL;
//     append_token(&tokens5, new_token("echo", WORD));
//     append_token(&tokens5, new_token("hola", WORD));
//     append_token(&tokens5, new_token(">", REDIR_OUT_TRUNC));
//     append_token(&tokens5, new_token("outfile", WORD));
//     t_NodeAST *ast5 = parse_ast(tokens5);
//     print_ast(ast5, 0);

//     printf("\nCaso 6: ls -l /tmp\n");
//     t_token *tokens6 = NULL;
//     append_token(&tokens6, new_token("ls", WORD));
//     append_token(&tokens6, new_token("-l", WORD));
//     append_token(&tokens6, new_token("/tmp", WORD));
//     t_NodeAST *ast6 = parse_ast(tokens6);
//     print_ast(ast6, 0);

//     printf("\nCaso 7: cat < infile\n");
//     t_token *tokens7 = NULL;
//     append_token(&tokens7, new_token("cat", WORD));
//     append_token(&tokens7, new_token("<", REDIR_IN));
//     append_token(&tokens7, new_token("infile", WORD));
//     t_NodeAST *ast7 = parse_ast(tokens7);
//     print_ast(ast7, 0);

//     printf("\nCaso 8: echo hola > pene | cat\n");
//     t_token *tokens8 = NULL;
//     append_token(&tokens8, new_token("echo", WORD));
//     append_token(&tokens8, new_token("hola", WORD));
//     append_token(&tokens8, new_token(">", REDIR_OUT_TRUNC));
//     append_token(&tokens8, new_token("pene", WORD));
//     append_token(&tokens8, new_token("|", PIPE));
//     append_token(&tokens8, new_token("cat", WORD));
//     t_NodeAST *ast8 = parse_ast(tokens8);
//     print_ast(ast8, 0);

//     printf("\nCaso 9: (ls -l | grep minishell) > result\n");
//     t_token *tokens9 = NULL;
//     append_token(&tokens9, new_token("(", SUBSHELL));
//     append_token(&tokens9, new_token("ls", WORD));
//     append_token(&tokens9, new_token("-l", WORD));
//     append_token(&tokens9, new_token("|", PIPE));
//     append_token(&tokens9, new_token("grep", WORD));
//     append_token(&tokens9, new_token("minishell", WORD));
//     append_token(&tokens9, new_token(")", SUBSHELL));
//     append_token(&tokens9, new_token(">", REDIR_OUT_TRUNC));
//     append_token(&tokens9, new_token("result", WORD));
//     t_NodeAST *ast9 = parse_ast(tokens9);
//     print_ast(ast9, 0);

//     printf("\nCaso 10: (echo ok && ls) || echo fail\n");
//     t_token *tokens10 = NULL;
//     append_token(&tokens10, new_token("(", SUBSHELL));
//     append_token(&tokens10, new_token("echo", WORD));
//     append_token(&tokens10, new_token("ok", WORD));
//     append_token(&tokens10, new_token("&&", AND));
//     append_token(&tokens10, new_token("ls", WORD));
//     append_token(&tokens10, new_token(")", SUBSHELL));
//     append_token(&tokens10, new_token("||", OR));
//     append_token(&tokens10, new_token("echo", WORD));
//     append_token(&tokens10, new_token("fail", WORD));
//     t_NodeAST *ast10 = parse_ast(tokens10);
//     print_ast(ast10, 0);

//     printf("\nCaso 11: cat < in | grep a | sort > out\n");
//     t_token *tokens11 = NULL;
//     append_token(&tokens11, new_token("cat", WORD));
//     append_token(&tokens11, new_token("<", REDIR_IN));
//     append_token(&tokens11, new_token("in", WORD));
//     append_token(&tokens11, new_token("|", PIPE));
//     append_token(&tokens11, new_token("grep", WORD));
//     append_token(&tokens11, new_token("a", WORD));
//     append_token(&tokens11, new_token("|", PIPE));
//     append_token(&tokens11, new_token("sort", WORD));
//     append_token(&tokens11, new_token(">", REDIR_OUT_TRUNC));
//     append_token(&tokens11, new_token("out", WORD));
//     t_NodeAST *ast11 = parse_ast(tokens11);
//     print_ast(ast11, 0);

//     // Libera memoria si lo necesitas
//     // free_token_list(tokens1); etc.
//     // free_ast(ast1); etc.

//     return 0;
// }
