/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/11 06:52:34 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/10 17:00:17 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

int	ft_strbegin(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] != '\0')
	{
		if (ft_strchr_ex(set, s1[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

int	ft_strend(char const *s1, char const *set)
{
	int	i;

	i = ft_strlen((char *)s1);
	while (i >= 0)
	{
		if (ft_strchr_ex(set, s1[i]) == 0)
			break ;
		i--;
	}
	return (i + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		begin;
	int		end;
	char	*dest;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return ((char *)s1);
	begin = ft_strbegin(s1, set);
	end = ft_strend(s1, set);
	if (begin >= end)
		return (ft_strdup(""));
	dest = malloc(sizeof(char) * (end - begin + 1));
	if (dest == NULL)
		return (NULL);
	ft_strlcpy(dest, (char *)s1 + begin, end - begin + 1);
	return (dest);
}
