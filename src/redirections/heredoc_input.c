/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 13:16:45 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/26 13:16:46 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/expansion.h"

void	process_line(int tmp_file, char *line, int quot, t_env *env)
{
	char	*expanded;

	if (!quot)
	{
		expanded = expand_dollar_line(line, env);
		line = ft_strdup(expanded);
		free(expanded);
	}
	if (!line)
		return ;
	write(tmp_file, line, ft_strlen(line));
	write(tmp_file, "\n", 1);
	free(line);
}

static void	remove_trailing_newline(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

static int	check_signal_interrupt(char *line, int *exit_from_signal)
{
	if (g_signal_value == SIGINT)
	{
		if (line)
			free(line);
		*exit_from_signal = EXIT_FROM_SIGNAL;
		return (1);
	}
	return (0);
}

static int	heredoc_loop(int file, char *clean_delim, int quotes, t_env *env)
{
	char	*line;
	int		exit_from_signal;

	exit_from_signal = 0;
	while (1)
	{
		write(STDOUT_FILENO, READLINE_HEREDOC, ft_strlen(READLINE_HEREDOC));
		line = get_next_line(STDIN_FILENO);
		if (check_signal_interrupt(line, &exit_from_signal))
			break ;
		if (!line)
		{
			printf("\n");
			break ;
		}
		remove_trailing_newline(line);
		if (ft_strcmp(line, clean_delim) == 0)
		{
			free(line);
			break ;
		}
		process_line(file, line, quotes, env);
	}
	return (exit_from_signal);
}

int	read_heredoc_input(int tmp_file, char *delimitter, t_env *env)
{
	char	*clean_delim;
	int		quotes;
	int		exit_from_signal;

	quotes = has_quotes(delimitter);
	setup_heresignals(&exit_from_signal);
	if (quotes)
		clean_delim = remove_quotes(delimitter);
	else
		clean_delim = delimitter;
	exit_from_signal = heredoc_loop(tmp_file, clean_delim, quotes, env);
	if (quotes)
		free(clean_delim);
	return (exit_from_signal);
}
