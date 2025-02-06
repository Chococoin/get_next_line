/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:18:42 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/02/06 19:21:17 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <string.h>

void	fill_line(char *buffer, char **line, char **store)
{
	int	i;
	int	j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	*line = malloc(sizeof(char) * (i + 2));
	if (!*line)
		return;
	ft_memcpy(*line, buffer, i);
	(*line)[i] = '\n';
	(*line)[i + 1] = '\0';
	if (buffer[i] == '\n')
		i++;
	j = ft_strlen(buffer) - i;
	*store = malloc(sizeof(char) * (j + 1));
	if (!*store)
		return;
	ft_memcpy(*store, buffer + i, j);
	(*store)[j] = '\0';
}

void	get_from_read(int fd, char **line, char **store)
{
	int		byteslen;
	char	buffer[BUFFER_SIZE + 1];

	buffer[0] = '\0';
	while (!ft_strchr(buffer, '\n'))
	{
		byteslen = read(fd, buffer, BUFFER_SIZE);
		if (byteslen > 0 && ft_strchr(buffer, '\n'))
		{
			fill_line(buffer, line, store);
		}
	}
	return ;
}

void	get_from_store(char **store, char **line)
{
	char 	*ptr;
	int		len;

	ptr = ft_strchr(*store, '\n');
	if (ptr)
	{
		len = ptr - *store + 1;
		*line = malloc(len + 1);
		if (!*line)
			return ;
		ft_memcpy(*line, *store, len);
		(*line)[len] = '\0';
		ptr = ft_strdup(*store + len);
		free(*store);
		*store = ptr;
	}
	return ;
}

char	*get_next_line(int fd)
{
	static char	*store;
	char		*line;

	line = NULL;
	if (!store)
		get_from_read(fd, &line, &store);
	else
		get_from_store(&store, &line);
	return (line);
}

int	main(void)
{
	int	fd;

	fd = open("sample.txt", O_RDONLY);
	printf("From main 1: %s", get_next_line(fd));
	printf("From main 2: %s", get_next_line(fd));
	printf("From main 3: %s", get_next_line(fd));
	close(fd);
	return (0);
}
