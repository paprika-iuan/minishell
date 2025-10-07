/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tests.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 12:21:56 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/07 12:21:58 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../inc/parser.h"

// void print_cmd_path_cb(t_NodeAST *node, void *ctx)
// {
// 	t_env *env = (t_env *)ctx;
//     char *path = set_cmd_path(node, env);
//     if (path)
//         printf("%s\n", path);
//     else
//         printf("command not found: %s\n", node->cmd.args[0]);
// }

// void	cmd_iter(t_NodeAST *n, void (*f)(t_NodeAST *, void *), void *ctx)
// {
// 	if (!node)
// 		return ;
// 	if (node->type == NODE_CMD)
// 	{
// 		f(node, ctx);
// 		return ;
// 	}
// 	if (node->type == NODE_SUBSHELL)
// 	{
// 		cmd_iter(node->subshell.reparse, f, ctx);
// 		return ;
// 	}
// 	if (node->type == NODE_PIPE || node->type == NODE_AND
// 			|| node->type == NODE_OR)
// 	{
// 		cmd_iter(node->binary.left, f, ctx);
// 		cmd_iter(node->binary.right, f, ctx);
// 		return ;
// 	}
// }
