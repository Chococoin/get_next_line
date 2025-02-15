/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: glugo-mu <glugo-mu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:42:49 by glugo-mu          #+#    #+#             */
/*   Updated: 2025/02/15 10:15:16 by glugo-mu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

size_t	ft_strlen(const char *c);
char	*ft_strchr(const char *s, int c);
char	*get_next_line(int fd);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);

# ifdef DEBUG_MEMORY  // 🚀 Activar depuración solo si se define DEBUG_MEMORY
void *debug_malloc(size_t size, const char *file, int line);
void debug_free(void *ptr, const char *file, int line);
#  define malloc(size) debug_malloc(size, __FILE__, __LINE__)
#  define free(ptr) debug_free(ptr, __FILE__, __LINE__)
# endif // DEBUG_MEMORY

#endif // GET_NEXT_LINE_H

