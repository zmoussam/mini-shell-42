/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strarr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 20:54:40 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/01 00:13:55 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>

void	ft_free_strarr(char **strarr)
{
	size_t	i;

	if (strarr)
	{
		i = 0;
		while (strarr[i])
			free(strarr[i++]);
		free(strarr);
	}
}
