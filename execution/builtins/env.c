/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/06 18:16:21 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/12 18:21:37 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	env_cmd(t_parser_node *root)
{
	if (root->ac != 1)
	{
		if (root->av[1][0] == '-')
		{
			printf("env: illegall option %s\n", root->av[1]);
			printf("usage: env whit no option or argument\n");
			g_lbv.exit_status = 1;
			return ;
		}
		else 
			printf("env: %s: No such file or directory\n", root->av[1]);
		g_lbv.exit_status = 127;
	}
	else
		print_list();
	g_lbv.exit_status = 0;
}
