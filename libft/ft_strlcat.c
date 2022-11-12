/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:47:05 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/12 14:06:07 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	ldest;
	unsigned int	i;
	unsigned int	result;

	ldest = 0;
	i = 0;
	result = 0;
	while (dest[ldest])
		ldest++;
	while (src[result])
		result++;
	if (size <= ldest)
		result += size;
	else
		result += ldest;
	while (src[i] && (ldest + 1) < size)
	{
		dest[ldest] = src[i];
		ldest++;
		i++;
	}
	dest[ldest] = '\0';
	return (result);
}
