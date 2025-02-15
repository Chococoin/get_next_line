/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:18:42 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/02/15 12:35:32 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

# ifdef DEBUG_MEMORY

void *debug_malloc(size_t size, const char *file, int line)
{
    void *ptr = __builtin_malloc(size);
    printf("[MALLOC] %p (%zu bytes) at %s:%d\n", ptr, size, file, line);
    return ptr;
}

void debug_free(void *ptr, const char *file, int line)
{
    printf("[FREE] %p at %s:%d\n", ptr, file, line);
    __builtin_free(ptr);
}
# endif

void	add_to_store(char **store, char *buffer, int start)
{
	int		buff_len;
	int		store_len;
	char	*new_store;

	buff_len = ft_strlen(buffer + start);
	store_len = 0;
	if (*store)
		store_len = ft_strlen(*store);
	if (buff_len > 0)
	{
		new_store = malloc(sizeof(char) * (store_len + buff_len + 1));
		if (!new_store)
			return ;
		if (*store)
		{
			ft_memcpy(new_store, *store, store_len);
			free(*store);
		}
		ft_memcpy(new_store + store_len, buffer + start, buff_len);
		new_store[store_len + buff_len] = '\0';
		*store = new_store;
	}
}

void	fill_line(char *buffer, char **line, char **store)
{
	int		store_len;
	int		buffer_len;
	char	*new_line;

	store_len = 0;
	if (*store)
		store_len = ft_strlen(*store);
	buffer_len = 0;
	while (buffer[buffer_len] && buffer[buffer_len] != '\n')
		buffer_len++;
	new_line = malloc(sizeof(char) * (store_len + buffer_len + 2));
	if (!new_line)
		return ;
	ft_memcpy(new_line, *store, store_len);
	ft_memcpy(new_line + store_len, buffer, buffer_len);
	if (*store)
		free(*store);
	*store = NULL;
	if (buffer[buffer_len] == '\n')
		new_line[store_len + buffer_len++] = '\n';
	new_line[store_len + buffer_len] = '\0';
	*line = new_line;
	if (buffer[buffer_len])
		add_to_store(store, buffer + buffer_len, 0);
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

void	get_from_read(int fd, char **line, char **store)
{
	int		byteslen;
	char	buffer[BUFFER_SIZE + 1];

	buffer[0] = '\0';
	while (!ft_strchr(buffer, '\n') && (!*store || !ft_strchr(*store, '\n')))
	{
		byteslen = read(fd, buffer, BUFFER_SIZE);
		if (byteslen <= 0)
		{
			if (*store && **store)
			{
				*line = ft_strdup(*store);
				free(*store);
				*store = NULL;
			}
			return ;
		}
		buffer[byteslen] = '\0';
		add_to_store(store, buffer, 0);
	}
	if (ft_strchr(*store, '\n'))
		get_from_store(store, line);
}

char	*get_next_line(int fd)
{
	static char	*store;
	char		*line;

	line = NULL;
	if (fd < 0)
		return (NULL);
	if (!store || !ft_strchr(store, '\n'))
		get_from_read(fd, &line, &store);
	else
		get_from_store(&store, &line);
	if (line)
		return (line);
	return (NULL);
}

int main(void)
{
	int		fd;
	char	*line;

	fd = open("sample.txt", O_RDONLY);
	if (fd < 0)
		return (1);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		// free(line);
	}
	close(fd);
	return (0);
}
