/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/26 11:41:57 by syakoubi          #+#    #+#             */
/*   Updated: 2021/12/26 11:42:17 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stddef.h>

char	*ft_strmapi(char const *s, char (*f)(size_t, char))
{
	char	*mapped;
	size_t	len;
	size_t	i;

	len = ft_strlen(s);
	mapped = malloc(len + 1);
	if (!mapped)
		return (NULL);
	i = 0;
	while (s[i])
	{
		mapped[i] = f(i, s[i]);
		i++;
	}
	mapped[i] = '\0';
	return (mapped);
}
