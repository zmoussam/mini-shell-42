/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:41:55 by syakoubi          #+#    #+#             */
/*   Updated: 2021/12/26 11:42:16 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <sys/types.h>

ssize_t	ft_putnbr_fd(int n, int fd)
{
	char	*str;
	ssize_t	count;

	str = ft_itoa(n);
	if (!str)
		return (-1);
	count = ft_putstr_fd(str, fd);
	free(str);
	return (count);
}
