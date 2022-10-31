/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:41:57 by zmoussam          #+#    #+#             */
/*   Updated: 2022/10/31 19:13:53 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/builtins.h"
#include<stdlib.h>
#include <unistd.h>
#include<stdio.h>

void	pwd(t_node *root)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (root->argc == 1)
		printf("%s\n", cwd);
	else
	{
		printf("minishel v0.1: pwd: %s: illegal option\n", root->argv[1]);
		printf("Usage: pwd []\n");
	}
	free(cwd);
}
