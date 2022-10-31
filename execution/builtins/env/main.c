/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:59:00 by zmoussam          #+#    #+#             */
/*   Updated: 2022/10/31 20:55:57 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

int main(int ac, char *av[], char *env[])
{
    t_env_list  *list;
    list = create_env(env);
    if (env_find(list,"VSN", -1))
	    printf("%s\n",  env_find(list,"VSCODE_GIT_ASKPASS_MAIN", -1)->content);
	return (0);
}
