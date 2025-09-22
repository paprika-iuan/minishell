/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 16:34:14 by amarquez          #+#    #+#             */
/*   Updated: 2025/09/11 16:34:49 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define HEADER "\033[1;36m\
███████╗ ██████╗ ██╗   ██╗     ██████╗ ██████╗ ███╗   ██╗ ██████╗██╗  ██╗ █████╗        ███████╗███╗   ██╗████████╗██████╗  ██████╗ \n\
██╔════╝██╔═══██╗╚██╗ ██╔╝    ██╔════╝██╔═══██╗████╗  ██║██╔════╝██║  ██║██╔══██╗       ██╔════╝████╗  ██║╚══██╔══╝██╔══██╗██╔═══██╗\n\
███████╗██║   ██║ ╚████╔╝     ██║     ██║   ██║██╔██╗ ██║██║     ███████║███████║       █████╗  ██╔██╗ ██║   ██║   ██████╔╝██║   ██║\n\
╚════██║██║   ██║  ╚██╔╝      ██║     ██║   ██║██║╚██╗██║██║     ██╔══██║██╔══██║       ██╔══╝  ██║╚██╗██║   ██║   ██╔══██╗██║   ██║\n\
███████║╚██████╔╝   ██║       ╚██████╗╚██████╔╝██║ ╚████║╚██████╗██║  ██║██║  ██║▄█╗    ███████╗██║ ╚████║   ██║   ██║  ██║╚██████╔╝\n\
╚══════╝ ╚═════╝    ╚═╝        ╚═════╝ ╚═════╝ ╚═╝  ╚═══╝ ╚═════╝╚═╝  ╚═╝╚═╝  ╚═╝╚═╝    ╚══════╝╚═╝  ╚═══╝   ╚═╝   ╚═╝  ╚═╝ ╚═════╝ \n\
\033[0m"

# define READLINE_MSG "\033[1;31m[🏓wanghao]\033[35m$> \033[0m"
# define SUCCESS 1

# include "../libft/libft.h"

# include <stdio.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>

int	echo(char **argv);

/****** LEXER ******/

int is_operand(char c);
int get_operand_length(char *line);
int get_quote_length(char *line);
int get_word_length(char *line);
int	handle_quote_length(char **line, int len);
int	count_tokens(char *line);
char	*allocate_token(int size);
char	**lexer(char *line, int	*num_tokens);

/****** IDENTIFIER ******/

enum token_type
{
	AND_OR,
	PIPE,
	SUBSHELL,
	WORD,
	REDIR
};

typedef struct s_token
{
	enum token_type	type;
	char		*content;
	int			position;
	struct s_token *next;
}	t_token;

t_token	*tokenizer(char *line);

#endif
