/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 12:13:22 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/04 22:00:29 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# define ENCODED_DOUBLEQ	-1
# define ENCODED_SINGLEQ	-2

# include "libft.h"
# include <stdbool.h>

typedef enum s_quote_mode
{
	UNQUOTED,
	SINGLE_QUOTED,
	DOUBLE_QUOTED,
}	t_quote_mode;

char			*encode_quotes(char *s);
char			*remove_quotes_enc(char *s);
char			*remove_quotes(char *s);
t_quote_mode	switch_quote_mode(t_quote_mode mode, char next_char);
t_quote_mode	switch_quote_mode_enc(t_quote_mode mode, char next_char);
bool			is_glob_enc(char *s);
bool			glob_match_enc(const char *p, const char *s);
char			**lst_to_strarr(t_list *lst);
void			close_pipe(int fd[2]);

#endif /* UTILS_H */
