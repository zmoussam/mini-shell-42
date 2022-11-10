/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_match.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 16:37:49 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/09 15:35:05 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"


bool    is_match(char *s, char *name, int mode)
{
    char *str = name;
    
    while(1)
    {
        while (mode == 1 || mode == 2)
            mode = change_mode(mode, *s++);
        if (*s == '\0')
            return (*name == '\0');
        else if (mode == 0 && *s == '*')
        {
            while (mode == 1 || mode == 2
                || (mode == 0 && *s == '*'))
                mode = change_mode(mode, *s++);
            if ((*name == '.' && name == str))
                return (false);
            if (*s == '\0')
                return (true);
            while (*name != '\0')
                if (is_match(s, name++, mode))
                    return (true);
            return (false);
        }
        else if (*s++ != *name++)
            return (false);
    }
}