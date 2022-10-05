/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_glob_enc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 13:29:36 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/28 04:23:52 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <stdbool.h>

bool	is_glob_enc(char *s)
{
	t_quote_mode	mode;

	mode = UNQUOTED;
	while (*s)
	{
		if (mode == UNQUOTED && *s == '*')
			return (true);
		mode = switch_quote_mode_enc(mode, *s);
		s++;
	}
	return (false);
}
