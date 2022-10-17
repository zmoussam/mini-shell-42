/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 19:41:30 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/12 21:03:12 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "libft.h"
#include <sys/types.h>
#include <stddef.h>
#include <unistd.h>
#include <stdlib.h>

t_file	*ft_file_new(int fd)
{
	t_file	*f;

	f = malloc(sizeof(t_file));
	if (f == NULL)
		return (NULL);
	f->buffer_len = 0;
	f->buffer_start = 0;
	f->fd = fd;
	return (f);
}

ssize_t	ft_file_fill_buffer(t_file *f)
{
	size_t	n;
	ssize_t	readc;

	n = BUFFER_SIZE - f->buffer_len;
	if (n == 0)
		return (0);
	ft_memmove(f->buffer, f->buffer + f->buffer_start, f->buffer_len);
	f->buffer_start = f->buffer_len;
	readc = read(f->fd, f->buffer + f->buffer_start, n);
	if (readc != -1)
		f->buffer_len += readc;
	return (readc);
}
