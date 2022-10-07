/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:41:58 by syakoubi          #+#    #+#             */
/*   Updated: 2021/12/26 11:42:17 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>
#include <stdlib.h>

char	*ft_substr(char const *s, size_t start, size_t len)
{
	char	*sub;

	start = ft_strnlen(s, start);
	len = ft_strnlen(s + start, len);
	sub = malloc(len + 1);
	if (sub)
	{
		ft_memcpy(sub, s + start, len);
		sub[len] = '\0';
	}
	return (sub);
}
