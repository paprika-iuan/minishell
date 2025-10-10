/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_pipe_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:26:02 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/07 15:26:04 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	allocate_child_pids(t_pipe_struct *t_pipe)
{
	t_pipe->child_pids = malloc((t_pipe->num_pipes + 1) * sizeof(pid_t));
	if (!t_pipe->child_pids)
	{
		printf("Memory allocation failed for child_pids\n");
		return (FAILURE);
	}
	return (SUCCESS);
}

int	wait_for_children(t_pipe_struct *t_pipe)
{
	int		status;
	pid_t	last_pid;
	pid_t	waited_pid;
	int		last_cmd_status;
	int		i;

	last_pid = t_pipe->child_pids[t_pipe->num_pipes];
	last_cmd_status = 0;
	i = 0;
	while (i < t_pipe->num_pipes + 1)
	{
		waited_pid = waitpid(-1, &status, 0);
		if (waited_pid == last_pid && WIFEXITED(status))
			last_cmd_status = WEXITSTATUS(status);
		else if (waited_pid == last_pid && WIFSIGNALED(status))
			last_cmd_status = EXIT_FROM_SIGNAL + WTERMSIG(status);
		i++;
	}
	return (last_cmd_status);
}
