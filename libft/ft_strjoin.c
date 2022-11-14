/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/13 20:01:06 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/13 18:52:55 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*s;
	int		len;
	int		l1;
	int		l2;

	if (!s1)
		s1 = ft_strdup("");
	if (!s2)
		s2 = ft_strdup("");
	l1 = ft_strlen((char *)s1);
	l2 = ft_strlen((char *)s2);
	len = l1 + l2;
	s = malloc((len + 1) * sizeof(char));
	if (s == NULL)
		return (NULL);
	ft_memmove(s, s1, l1);
	ft_memmove((s + l1), s2, l2);
	s[len] = '\0';
	return (s);
}
