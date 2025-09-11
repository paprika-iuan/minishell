/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarquez <amarquez@student.42barcelon      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/28 09:47:02 by amarquez          #+#    #+#             */
/*   Updated: 2025/06/04 16:05:18 by amarquez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*read_and_append(int fd, char *stash, ssize_t *bytes_read)
{
	char	*tmp;
	char	*buf;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	*bytes_read = read(fd, buf, BUFFER_SIZE);
	if (*bytes_read < 0)
	{
		free(stash);
		free(buf);
		return (NULL);
	}
	else if (*bytes_read == 0)
	{
		free(buf);
		return (stash);
	}
	buf[*bytes_read] = '\0';
	tmp = ft_strjoin(stash, buf);
	free(buf);
	free(stash);
	return (tmp);
}

static char	*read_until_newline(int fd, char *stash)
{
	ssize_t	bytes_read;

	if (!stash)
	{
		stash = ft_calloc(1, sizeof(char));
		if (!stash)
			return (NULL);
	}
	bytes_read = 0;
	while (!ft_strchr(stash, '\n'))
	{
		stash = read_and_append(fd, stash, &bytes_read);
		if (!stash)
			return (NULL);
		else if (bytes_read == 0)
		{
			if (stash[0] == '\0')
			{
				free(stash);
				return (NULL);
			}
			return (stash);
		}
	}
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash = NULL;
	char		*line;
	char		*tmp;
	char		*nl_pos;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_until_newline(fd, stash);
	if (!stash)
		return (NULL);
	nl_pos = ft_strchr(stash, '\n');
	if (nl_pos)
	{
		line = ft_strndup(stash, nl_pos - stash + 1);
		tmp = ft_strndup(nl_pos + 1, ft_strlen(nl_pos + 1));
		free(stash);
		stash = tmp;
	}
	else
	{
		line = ft_strndup(stash, ft_strlen(stash));
		free(stash);
		stash = NULL;
	}
	return (line);
}
/*
int	ft_open(char *filename)
{
	int	fd_to_read;

	fd_to_read = open(filename, O_RDONLY);
	if (fd_to_read == -1)
	{
		printf("Couldn't open file.\n");
		return (-1);
	}
	return (fd_to_read);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("file.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening file");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
*/
