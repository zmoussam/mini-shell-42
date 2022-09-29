/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _internal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 22:12:33 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/30 14:40:22 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _INTERNAL_H
# define _INTERNAL_H

# include "lexer.h"
# include <stddef.h>

t_token	token_init(const char *s, size_t len, t_token_type type);
size_t	lexer_advance(t_lexer *lexer, size_t n);
size_t	lexer_skip_spaces(t_lexer *lexer);
t_token	lexer_eat(t_lexer *lexer, const char *s, t_token_type type);
t_token	lexer_eat_string(t_lexer *lexer);

#endif /* _INTERNAL_H */
