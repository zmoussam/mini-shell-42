/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:41:57 by zmoussam          #+#    #+#             */
/*   Updated: 2022/11/09 20:01:25 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include<stdlib.h>
#include <unistd.h>
#include<stdio.h>

void	pwd(t_parser_node *root)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (root->ac == 1)
	{
		if(cwd == NULL)
			printf("!!N.A.D == NO DIRECTORY\n");
		else 
			printf("%s\n", cwd);
	}
	else
	{
		printf("minishel v0.1: pwd: %s: illegal option\n", root->av[1]);
		printf("Usage: pwd []\n");
	}
	free(cwd);
}
