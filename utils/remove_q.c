/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_q.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 14:45:20 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/11 11:16:04 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lexer/lexer.h"

char	*remove_q(char	*str)
{
	char	*s;
	int		n;

	s = str;
	n = ft_strlen(s);
	while (*s)
	{
		if (*s == DEF_SINGEL_Q || *s == DEF_DOUBEL_Q)
			ft_memmove(s, s + 1, n);
		else
			s++;
		n--;
	}
	return (str);
}
