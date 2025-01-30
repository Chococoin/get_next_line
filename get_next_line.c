/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:18:42 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/01/30 16:25:18 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*warehouse;
	char		buffer[BUFFER_SIZE];
	int 		bytesRead;
	int 		i;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		i = 0;
		while(buffer[i])
		{
			if (buffer[i] == '\n')
				break;
			else 
				write(1, &buffer[i], 1);
			i++;
		}
	}
	write(1, &buffer, i);
	return warehouse;
}
