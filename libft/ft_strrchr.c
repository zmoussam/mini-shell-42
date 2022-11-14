/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 10:44:47 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/14 14:45:29 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strrchr(const char *str, int c)
{
	char	*dest;
	int		i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (i >= 0)
	{
		if (str[i] == (char)c)
		{
			dest = (char *)&str[i];
			return (dest);
		}
		i--;
	}
	if (str[i] == '\0' && c == '\0')
	{
		dest = (char *) &str[i];
		return (dest);
	}
	return (NULL);
}
