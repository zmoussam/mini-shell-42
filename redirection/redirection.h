/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 17:04:49 by zmoussam          #+#    #+#             */
/*   Updated: 2022/10/27 17:54:35 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIRECTION_H
#define REDIRECTION_H

typedef enum t_typerdc{
    HEREDOC,
    RDC_IN,
    RDC_OUT,
    DBL_RDC_OUT,
}t_typerdc;

typedef struct t_redc
{
    int type;
    char *file_name;
    struct t_redc *next;
}t_redc;
#endif