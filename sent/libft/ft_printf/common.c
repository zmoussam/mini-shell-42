/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:38:43 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/12 21:03:12 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/types.h>

void	ft_acc_writec(ssize_t bytes_written, ssize_t *writec)
{
	if (*writec != -1)
	{
		if (bytes_written == -1)
			*writec = -1;
		else
			*writec += bytes_written;
	}
}

void	ft_putstr_acc(const char *s, ssize_t *writec)
{
	if (*writec != -1)
		ft_acc_writec(ft_putstr_fd(s, 1), writec);
}

void	ft_putnstr_acc(const char *s, size_t n, ssize_t *writec)
{
	if (*writec != -1)
		ft_acc_writec(ft_putnstr_fd(s, n, 1), writec);
}

void	ft_putchar_acc(char c, ssize_t *writec)
{
	if (*writec != -1)
		ft_acc_writec(ft_putchar_fd(c, 1), writec);
}

void	ft_putul_acc(unsigned long n, const char *b, int pr, ssize_t *writec)
{
	if (ft_strlen(b) < 2)
		*writec = -1;
	else if (!n)
	{
		while (pr-- > 0)
			ft_putchar_acc('0', writec);
	}
	else
	{
		ft_putul_acc(n / ft_strlen(b), b, pr - 1, writec);
		ft_putchar_acc(b[n % ft_strlen(b)], writec);
	}
}
