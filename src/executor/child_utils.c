/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 15:26:02 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/17 11:53:16 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

int	allocate_child_pids(t_pipe_struct *t_pipe)
{
	char	*err_msg;

	t_pipe->child_pids = malloc((t_pipe->num_pipes + 1) * sizeof(pid_t));
	if (!t_pipe->child_pids)
	{
		err_msg = "Memory allocation failed for child_pids\n";
		ft_putstr_fd(err_msg, STDERR_FILENO);
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

void	cleanup_child(char *full_path, char **env_arr)
{
	int	i;

	if (full_path)
		free(full_path);
	i = 0;
	if (env_arr)
	{
		while (env_arr[i])
			free(env_arr[i++]);
		free(env_arr);
	}
}
