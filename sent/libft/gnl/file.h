/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 09:25:35 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/12 21:03:12 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H

# include "libft.h"
# include <stddef.h>

typedef struct s_file
{
	int		fd;
	char	buffer[BUFFER_SIZE];
	size_t	buffer_len;
	size_t	buffer_start;
}	t_file;

/*
 * Creates a new `t_file` instance for the file descriptor `fd`,
 * and returns a pointer to it that can be freed using `free`.
 * Returns NULL on allocation failure.
 */
t_file	*ft_file_new(int fd);

/*
 * Fills the t_file buffer with characters read from the corresponding
 * file descriptor and returns the number of characters that were added,
 * or -1 on error.
 * If the buffer is already full, no operation is performed and 0 is returned.
 */
ssize_t	ft_file_fill_buffer(t_file *file);

#endif /* FILE_H */
