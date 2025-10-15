/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 12:51:13 by amarquez          #+#    #+#             */
/*   Updated: 2025/10/14 12:51:15 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/parser.h"

// static void	read_heredoc_input(int tmp_file, char *delimiter)
// {
// 	char	*line;
// 	int		len;

// 	while (1)
// 	{
// 		write(1, "> ", 2);
// 		line = get_next_line(STDIN_FILENO);
// 		if (!line)
// 			break ;
// 		len = ft_strlen(line);
// 		if (len > 0 && line[len - 1] == '\n')
// 			line[len - 1] = '\0';
// 		if (ft_strcmp(line, delimiter) == 0)
// 		{
// 			free(line);
// 			break ;
// 		}
// 		line[len - 1] = '\n';
// 		write(tmp_file, line, ft_strlen(line));
// 		free(line);
// 	}
// }

// void	heredoc(char **argv, t_pipex *pipex)
// {
// 	int		tmp_file;
// 	char	*delimiter;

// 	// pipex->heredoc = 1;
// 	// delimiter = argv[2];
// 	// tmp_file = open("tmp", O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	// if (tmp_file < 0)
// 	// 	perror("Error creating here_doc");
// 	// read_heredoc_input(tmp_file, delimiter);
// 	// close(tmp_file);
// 	// pipex->infile = open("tmp", O_RDONLY);
// 	// if (pipex->infile < 0)
// 	// {
// 	// 	unlink("tmp");
// 	// 	perror("Error opening here_doc");
// 	// }
// }
