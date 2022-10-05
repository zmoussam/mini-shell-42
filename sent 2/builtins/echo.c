/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 18:41:03 by zmoussam          #+#    #+#             */
/*   Updated: 2022/10/02 18:52:33 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/builtins.h"
#include <stdio.h>

void    echo(t_node *root)
{
    int i;
    int j;
    int k;

    i = 1;
    k = 0;
    j = 2;
    if (root->argv[i] && (root->argv[i][0] == '-' && root->argv[i][1] == '\0'))
        i++;
    else if (root->argv[i] && root->argv[i][0] == '-' && root->argv[i][1] == 'n')
    {
        while (root->argv[i][j] && root->argv[i][j] == 'n')
            j++;
        if (root->argv[i][j] == '\0')
        {
            i++;
            k = 1;
        }
    }
    while (root->argv[i])
    {
        printf("%s", root->argv[i]);
        i++;
        if (i != root->argc)
            printf(" ");
    }
    if (k == 0)
        printf("\n");
}