/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 11:42:24 by mel-hous          #+#    #+#             */
/*   Updated: 2022/10/07 15:08:07 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

void    *manu(t_env_node   *var, char *s)
{
    int j;

    j = 0;
    while (s[j])
    {
        if (s[j] == '=')
            add_back(&var, new_node(ft_substr(s, j + 1, -1),ft_substr(s, 0, j), j));
        j++;
    }
    return(var);
}

t_env_node *create_env(char *env[])
{
    t_env_node *var;
    int i;

    i = 0;
    var = NULL;
    while (env[i])
    {
        var = manu(var, env[i]);
        i++;
    }
    return(var);
}
