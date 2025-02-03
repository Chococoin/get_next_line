/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:18:42 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/02/03 14:34:30 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	get_line(int fd, char *line, char *buffer)
{
	int	i;
	int	byteslen;
	
	while ((byteslen = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		line[byteslen] = '\0';
		i = 0;
		if (buffer[0] != '\0')
		{
			while (buffer[i] != '\n' && buffer[i] != '\0')
			{
				printf("Buffer: %c\n", buffer[i]);
				line[i] = buffer[i];
				i++;
			}
			if (buffer[i] == '\n')
				break ;
		}
	}
}

char	*get_next_line(int fd)
{
	// static char	warehouse;
	char		buffer[BUFFER_SIZE + 1];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!line)
			return (NULL);
	get_line(fd, line, buffer);

	printf("Buffer after while: /*%s*/\n", buffer);
	
	return (line);
}

int	main(void)
{
	int	fd;

	fd = open("sample2.txt", O_RDONLY);
	printf("From main 1: %s\n", get_next_line(fd));
	printf("From main 2: %s\n", get_next_line(fd));
	close(fd);
	return (0);
}
