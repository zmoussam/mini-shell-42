/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   av_creat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 09:58:13 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/05 20:44:18 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

char **av_creat(t_cmd **lst)
{
    char **av;
    int i;
    int size;
    t_cmd *list;

    i = 0;
    list = *lst;
    size = cmd_size(list);
    av = malloc(sizeof(char *) * size + 1);
    if(!av)
        return(NULL);
    while(list)
    {
        if (list->wc)
            while(list->wc)
            {
                av[i++] = list->wc->d_name;
                list->wc = list->wc->next;
            }
        av[i++] = list->word;
       list = list->next;
    }
    if (av)
        av[i] = NULL;
    cmd_clear(lst);
    return(av);
}