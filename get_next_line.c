/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:18:42 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/02/10 17:55:05 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	add_to_store(char **store, char *buffer, int buffer_len)
{
	if (buffer_len > 0)
	{
		*store = malloc(sizeof(char) * (buffer_len + 1));
		if (!*store)
			return ;
		ft_memcpy(*store, buffer, buffer_len);
		(*store)[buffer_len] = '\0';
	}
}

void	fill_line(char *buffer, char **line, char **store)
{
	int store_len;
	int buffer_len;

	store_len = 0;
	if (*store)
		store_len = ft_strlen(*store);
	buffer_len = 0;
	while (buffer[buffer_len] && buffer[buffer_len] != '\n')
		buffer_len++;
	*line = malloc(sizeof(char) * (store_len + buffer_len + 2));
	if (!*line)
		return ;
	if (*store)
	{
		ft_memcpy(*line, *store, store_len);
		free(*store);
		*store = NULL;
	}
	ft_memcpy(*line + store_len, buffer, buffer_len);
	(*line)[store_len + buffer_len] = '\n';
	(*line)[store_len + buffer_len + 1] = '\0';
	if (buffer[buffer_len + 1] == '\n')
		buffer_len++;
	add_to_store(store, buffer, buffer_len);
}

void	get_from_read(int fd, char **line, char **store)
{
	int		byteslen;
	char	buffer[BUFFER_SIZE + 1];

	buffer[0] = '\0';
	while (!ft_strchr(buffer, '\n') && !ft_strchr(*line, '\n'))
	{
		byteslen = read(fd, buffer, BUFFER_SIZE);
		if (ft_strchr(*store, '\n') || (byteslen > 0 && ft_strchr(buffer, '\n')))
			fill_line(buffer, line, store);
		else if (byteslen > 0 && !ft_strchr(buffer, '\n'))
			add_to_store(store, buffer, byteslen);
	}
	return ;
}

void	get_from_store(char **store, char **line)
{
	char	*ptr;
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

	if (fd < 0)
		return (NULL);
	line = NULL;
	if (!store || !ft_strchr(store, '\n'))
		get_from_read(fd, &line, &store);
	else
		get_from_store(&store, &line);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("sample.txt", O_RDONLY);
	while (fd >= 0)
	{
		line = get_next_line(fd);
		printf("%s", line);
	}
	close(fd);
	return (0);
}
