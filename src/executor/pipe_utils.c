/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 15:57:29 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/02 15:57:32 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

static int	search_pipes(t_NodeAST *node)
{
	int	count;

	count = 0;
	if (!node)
		return (0);
	if (node->type == NODE_PIPE)
	{
		count = 1;
		count += search_pipes(node->binary.right);
	}
	return (count);
}

static int	allocate_pipes(t_pipe_struct *t_pipe)
{
	t_pipe->pipes = malloc((t_pipe->num_pipes * 2) * sizeof(int));
	if (!t_pipe->pipes)
	{
		printf("Memory allocation failed for pipes\n");
		return (FAILURE);
	}
	t_pipe->pipe_idx = 0;
	return (SUCCESS);
}

static int	create_pipes(t_pipe_struct *pipe_struct)
{
	int	i;

	i = 0;
	while (i < pipe_struct->num_pipes)
	{
		if (pipe(pipe_struct->pipes + 2 * i) < 0)
		{
			printf("Pipe creation failed\n");
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

int	set_pipes(t_pipe_struct *t_pipe, t_NodeAST *node)
{
	t_pipe->num_pipes = search_pipes(node);
	if (!allocate_pipes(t_pipe))
		return (FAILURE);
	if (!create_pipes(t_pipe))
		return (FAILURE);
	return (SUCCESS);
}

void	close_pipes(t_pipe_struct *t_pipe)
{
	int	i;

	if (!t_pipe->pipes)
		return ;
	i = 0;
	while (i < (t_pipe->num_pipes * 2))
	{
		close(t_pipe->pipes[i]);
		i++;
	}
	free(t_pipe->pipes);
}
