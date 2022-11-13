/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 12:47:29 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/13 12:56:29 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

#define NO_EXPANSION	((char *)-1)

char	*ft_exp(char *expnd, char **s)
{
	expnd = exit_status(s);
	if (expnd == NO_EXPANSION)
		expnd = exp_var(s);
	return (expnd);
}
