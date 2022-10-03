/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_simple_cmd_elem.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 04:36:02 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/25 18:38:18 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_internal.h"
#include "lexer.h"
#include "libft.h"

t_list	*parse_cmd_elem(
		t_lexer *lexer,
		t_list **rdrlst,
		t_list **arglst
	)
{
	t_list	*ret;

	if (lexer_peek(lexer).type == STRING)
	{
		ret = expand_glob(lexer_next(lexer));
		if (ret)
			ft_lstadd_back(arglst, ret);
	}
	else
		ret = parse_rdr(lexer, rdrlst);
	return (ret);
}
