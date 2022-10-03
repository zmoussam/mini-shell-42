/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:41:54 by syakoubi          #+#    #+#             */
/*   Updated: 2021/12/26 11:42:03 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char		*_dst;
	const char	*_src;

	_dst = dst;
	_src = src;
	if (src < dst)
	{
		while (n--)
			_dst[n] = _src[n];
	}
	else if (src > dst)
	{
		while (n--)
			*(_dst++) = *(_src++);
	}
	return (dst);
}
