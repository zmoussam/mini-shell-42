/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 04:00:14 by syakoubi          #+#    #+#             */
/*   Updated: 2022/02/11 04:10:24 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stddef.h>

char	*ft_strsep(char **str, const char *sep)
{
	char	*s;
	char	*end;

	s = *str;
	if (!s)
		return (NULL);
	end = s + ft_strcspn(s, sep);
	if (*end)
		*end++ = '\0';
	else
		end = NULL;
	*str = end;
	return (s);
}
