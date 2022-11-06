/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memchr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 09:04:32 by mel-hous          #+#    #+#             */
/*   Updated: 2021/11/16 08:01:06 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned char	*dest;
	size_t			i;

	dest = (unsigned char *)str;
	i = 0;
	while (i < n)
	{
		if (dest[i] == (unsigned char)c)
			return ((void *)&dest[i]);
		i++;
	}
	return (NULL);
}
