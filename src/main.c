/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/12 10:49:43 by amarquez          #+#    #+#             */
/*   Updated: 2025/09/12 10:49:45 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int argc, char **argv, char **envp)
{


	char	*input;
	char	**input_split;

	//printf("%s", HEADER);
	while (1)
	{
		input = readline(READLINE_MSG);
		if (!input)
			break ;
		add_history(input);
		input_split = ft_split(input, ' ');
		if (input_split)
		{
			if (input_split[0] && ft_strcmp(input_split[0], "echo") == 0)
				echo(input_split);
			else if (input_split[0])
				printf("You typed: %s\n", input);
			for (int i = 0; input_split[i]; i++)
				free(input_split[i]);
			free(input_split);
		}
		free(input);
	}
	rl_clear_history();
	return (0);
}
