/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:12:32 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/12 21:03:12 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "file.h"
#include "file_list.h"
#include <sys/types.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>

static char	*get_buffer_slice(t_file *f)
{
	char	*slice;
	size_t	len_slice;

	len_slice = ft_memcspn(f->buffer + f->buffer_start, "\n", f->buffer_len);
	if (len_slice < f->buffer_len)
		len_slice++;
	slice = ft_substr(f->buffer, f->buffer_start, len_slice);
	if (!slice)
		return (NULL);
	f->buffer_start += len_slice;
	f->buffer_len -= len_slice;
	return (slice);
}

static char	*append_buffer_slice(char *line, t_file *f)
{
	char	*slice;
	char	*tmp;

	slice = get_buffer_slice(f);
	if (!slice)
		return (NULL);
	if (!line)
		return (slice);
	tmp = ft_strjoin(line, slice);
	free(line);
	free(slice);
	return (tmp);
}

static char	*fget_next_line(t_file *f)
{
	char	*line;
	ssize_t	readc;

	line = NULL;
	while (1)
	{
		if (f->buffer_len == 0)
		{
			readc = ft_file_fill_buffer(f);
			if (readc == -1)
				break ;
			if (readc == 0)
				return (line);
		}
		line = append_buffer_slice(line, f);
		if (!line)
			return (NULL);
		if (ft_strchr(line, '\n'))
			return (line);
	}
	free(line);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static t_list	*lst;
	t_file			*f;
	char			*line;

	f = ft_file_get_or_create(&lst, fd);
	if (f == NULL)
		return (NULL);
	line = fget_next_line(f);
	if (!line)
		ft_file_delete(&lst, fd);
	return (line);
}
