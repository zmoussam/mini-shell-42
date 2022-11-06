/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:37:49 by mel-hous          #+#    #+#             */
/*   Updated: 2022/10/11 14:02:04 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"


bool    is_match(char *p, char *dir_n, int mode)
{
    char *full_str = dir_n;
    
    while(1)
    {
        while (mode == 1 || mode == 2)
            mode = change_mode(mode, *p++);
        if (*p == '\0')
            return (*dir_n == '\0');
        else if (mode == 0 && *p == '*')
        {
            while (mode == 1 || mode == 2
                || (mode == 0 && *p == '*'))
                mode = change_mode(mode, *p++);
            if ((*dir_n == '.' && dir_n == full_str))
                return (false);
            if (*p == '\0')
                return (true);
            while (*dir_n != '\0')
                if (is_match(p, dir_n++, mode))
                    return (true);
            return (false);
        }
        else if (*p++ != *dir_n++)
            return (false);
    }
}