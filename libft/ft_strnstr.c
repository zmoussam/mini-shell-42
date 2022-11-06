/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:22:02 by mel-hous          #+#    #+#             */
/*   Updated: 2021/11/15 15:16:22 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include"libft.h"

char	*ft_strnstr(const char *str, const char *sub, size_t n)
{
	size_t	i;
	int		j;

	if (*sub == '\0')
		return ((char *)str);
	i = 0;
	while (str[i] != '\0' && i < n)
	{
		if (str[i] == sub[0])
		{
			j = 0;
			while (sub[j] && str[i + j] && i + j < n
				&& str[i + j] == sub[j])
				j++;
			if (sub[j] == '\0')
				return ((char *)str + i);
		}
		i++;
	}
	return (0);
}
