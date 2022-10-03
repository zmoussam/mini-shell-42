/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:41:55 by syakoubi          #+#    #+#             */
/*   Updated: 2021/12/26 11:42:16 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>

ssize_t	ft_putendl_fd(const char *s, int fd)
{
	ssize_t	count;
	ssize_t	tmp;

	count = ft_putstr_fd(s, fd);
	if (count == -1)
		return (-1);
	tmp = ft_putchar_fd('\n', fd);
	if (tmp == -1)
		return (-1);
	return (count + tmp);
}
