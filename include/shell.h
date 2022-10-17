/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/17 00:35:08 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/25 18:53:24 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "libft.h"
# include "parser.h"

# define SH_NAME	"minishell"
# define SH_PS1		"$ "
# define SH_PS2		"> "

typedef struct s_sh_state
{
	t_list			*envlst;
	unsigned char	exit_status;
}	t_sh_state;

typedef int			(*t_builtin)(int, char **);

extern t_sh_state	g_sh_state;

int			sh_state_init(int argc, char **argv, char **envp);
void		sh_state_destroy(void);

#endif /* SHELL_H */
