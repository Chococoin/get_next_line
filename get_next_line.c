/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:18:42 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/01/31 18:24:40 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*warehouse;
	char		buffer[BUFFER_SIZE + 1];
	int 		bytesRead;
	char		temp[2];
	int 		i;
	
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while ((bytesRead = read(fd, buffer, BUFFER_SIZE)) > 0)
	{
		i = 0;
		while(buffer[i])
		{
			if (buffer[i] != '\n')
			{
			    temp[0] = buffer[i]; // Asignar el carácter a la cadena temporal
                temp[1] = '\0'; // Terminar la cadena con un carácter nulo
				warehouse = ft_strjoin(warehouse, temp);
			}
			else
			{
				warehouse = ft_strjoin(warehouse, "\n");
				break;
			}
			i++;
		}
	}
	return warehouse;
}
