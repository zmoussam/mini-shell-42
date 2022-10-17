/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _internal.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 19:18:13 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/25 18:38:54 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _INTERNAL_H
# define _INTERNAL_H

# define RULE_MISMATCH	((void *)-1)

# include "parser.h"
# include "lexer.h"

void	print_syntax_error(t_lexer *lexer, t_token token);

t_rdr	*rdr_init(t_rdr_type type, t_token str);
t_node	*node_init(t_node_type type, t_node *left, t_node *right);
void	rdr_destroy(t_rdr *rdr);
void	node_destroy(t_node *node);

char	*expand_params(const char *s);
t_list	*expand_glob(t_token token);
t_list	*expand(t_token token);

t_list	*parse_rdr(t_lexer *lexer, t_list **rdrlst);
t_list	*parse_cmd_elem(
			t_lexer *lexer,
			t_list **rdrlst,
			t_list **arglst
			);
t_node	*parse_cmd(t_lexer *lexer);
t_node	*parse_subshell(t_lexer *lexer);
t_node	*parse_cmd(t_lexer *lexer);
t_node	*parse_pipeline(t_lexer *lexer);
t_node	*parse_pipe(t_lexer *lexer);
t_node	*parse_or(t_lexer *lexer);
t_node	*parse_and(t_lexer *lexer);
t_node	*parse_conditional(t_lexer *lexer);
t_node	*parse_line(t_lexer *lexer);

#endif /* _INTERNAL_H */
