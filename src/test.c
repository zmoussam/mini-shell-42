/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 16:48:41 by zmoussam          #+#    #+#             */
/*   Updated: 2022/09/25 17:18:19 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/minishell.h"

int main(int arc, char **arv)
{
    char *str;
    cd("/Users/zmoussam/Desktop/minishell");
    
    while(1)
    {
        printf("minishell -v0.1  : %s", getcwd());
        str = readline("");
        add_history(str);  
        free(str);
    }
}