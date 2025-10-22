/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirbau- <jgirbau-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 13:11:27 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/20 10:26:59 by jgirbau-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"
#include "../../inc/expansion.h"

int	has_quotes(char *str)
{
	while (*str)
	{
		if (is_quote(*str))
			return (1);
		str++;
	}
	return (0);
}

char	*remove_quotes(char *str)
{
	char	*curr;
	char	*start;
	char	quote_char;
	int		size;

	curr = str;
	while (*curr && !is_quote(*curr))
		curr++;
	if (!*curr)
		return (NULL);
	quote_char = *curr;
	curr++;
	start = curr;
	size = 0;
	while (*curr && *curr != quote_char)
	{
		size++;
		curr++;
	}
	if (size == 0)
		return ((char *)ft_calloc(1, sizeof(char)));
	return (ft_strndup(start, size));
}

/*
char	*dollar_expanded_heredoc(char *args, t_env *env)
{
	char	*dollar_pos;
	char	*to_expand;
	int		var_len;
	char	*res;

	dollar_pos = ft_strchr(args, '$');
	if (!dollar_pos)
		return (NULL);
	var_len = count_var_len(dollar_pos, 1);
	if (!var_len)
		return (ft_strndup("$", 1));
	to_expand = ft_substr(dollar_pos + 1, 0, var_len);
	if (!to_expand)
		return (NULL);
	res = get_env_value(to_expand, env);
	free (to_expand);
	if (res)
		return (ft_strdup(res));
	return (NULL);
}

char	*join_before_dollar(char *line, int *i, t_env *env)
{
	char	*before;
	char	*dollar;
	char	*tmp;

	before = ft_substr(line, 0, *i);
	dollar = dollar_expanded(line, env);
	(*i)++;
	while (line[*i] && (ft_isalnum(line[*i]) || line[*i] == '_'))
		(*i)++;
	tmp = ft_strjoin(before, dollar);
	free(before);
	free(dollar);
	return (tmp);
}

char	*expand_dollar_line(char *line, t_env *env)
{
	int		i;
	char	*tmp;
	char	*after;
	char	*after_expanded;
	char	*res;

	i = 0;
	while (line[i] && line[i] != '$')
		i++;
	tmp = join_before_dollar(line, &i, env);
	after = ft_substr(line, i, ft_strlen(line));
	after_expanded = NULL;
	if (after && ft_strchr(after, '$'))
	{
		after_expanded = expand_dollar_line(after, env);
		res = ft_strjoin(tmp, after_expanded);
	}
	else
		res = ft_strjoin(tmp, after);
	free(tmp);
	free(after);
	free(after_expanded);
	return (res);
}
*/
void	process_line(int tmp_file, char *line, int quot, t_env *env)
{
	char	*expanded;

	if (!quot)
	{
		expanded = expand_dollar_line(line, env);
		free(line);
		line = expanded;
	}
	if (!line)
		return ;
	write(tmp_file, line, ft_strlen(line));
	write(tmp_file, "\n", 1);
	free(line);
}

void set_heresign(int sign)
{
	printf("\n");
	g_signal_value = sign;
}

int	read_heredoc_input(int tmp_file, char *delimitter, t_env *env)
{
	char				*line;
	char				*clean_delim;
	int					quotes;
	int					exit_from_signal;
	struct sigaction	sa;

	quotes = has_quotes(delimitter);
	exit_from_signal = 0;
	g_signal_value = 0;
	if (quotes)
		clean_delim = remove_quotes(delimitter);
	else
		clean_delim = delimitter;
	sa.sa_handler = set_heresign;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	while (1)
	{
		write(STDOUT_FILENO, READLINE_HEREDOC, ft_strlen(READLINE_HEREDOC));
		line = get_next_line(STDIN_FILENO);
		if (g_signal_value == SIGINT)
		{
			if (line)
				free(line);
			exit_from_signal = EXIT_FROM_SIGNAL;
			break ;
		}
		if (!line)
		{
			printf("\n");
			break ;
		}
		int len = ft_strlen(line);
		if (len > 0 && line[len - 1] == '\n')
			line[len - 1] = '\0';
		if (ft_strcmp(line, clean_delim) == 0)
		{
			free(line);
			break ;
		}
		process_line(tmp_file, line, quotes, env);
	}
	if (quotes)
		free(clean_delim);
	return (exit_from_signal);
}

char	*make_here_name(int id)
{
	char	*num;
	char	*name;
	char	*tmp;

	num = ft_itoa(id);
	tmp = ft_strjoin("/tmp/minishell_hd_", num);
	free(num);
	name = ft_strjoin(tmp, ".tmp");
	free(tmp);
	return (name);
}

static void	close_heredocs_in_redirects(t_NodeAST *redir)
{
	while (redir)
	{
		if (redir->redirect.type == REDIR_HEREDOC
			&& redir->redirect.fd >= 0)
			close(redir->redirect.fd);
		redir = redir->redirect.redirect;
	}
}

void	close_all_heredocs(t_NodeAST *node)
{
	if (!node)
		return ;
	if (node->type == NODE_CMD)
	{
		close_heredocs_in_redirects(node->cmd.redirect);
		return ;
	}
	if (node->type == NODE_SUBSHELL)
	{
		close_all_heredocs(node->subshell.reparse);
		close_heredocs_in_redirects(node->subshell.redirect);
		return ;
	}
	if (node->type == NODE_PIPE || node->type == NODE_AND
		|| node->type == NODE_OR)
	{
		close_all_heredocs(node->binary.left);
		close_all_heredocs(node->binary.right);
		return ;
	}
}
