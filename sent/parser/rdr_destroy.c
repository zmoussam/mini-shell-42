/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_destroy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 00:31:29 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/05 22:55:24 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <stdlib.h>
#include <unistd.h>

void	rdr_destroy(t_rdr *rdr)
{
	if (rdr->type == RDR_HEREDOC)
		unlink(rdr->f);
	free(rdr->f);
	free(rdr);
}
