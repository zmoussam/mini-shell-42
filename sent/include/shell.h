/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 00:35:08 by syakoubi          #+#    #+#             */
/*   Updated: 2022/09/29 19:05:33 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
# include "parser.h"

# define SH_NAME	"minishell"
# define SH_PS1		"minishel v0.1 >"
# define SH_PS2		"> "

typedef struct s_sh_state
{
	t_list			*envlst;
	unsigned char	exit_status;
}	t_sh_state;

typedef int			(*t_builtin)(int, char **);

extern t_sh_state	g_sh_state;

#endif /* SHELL_H */
