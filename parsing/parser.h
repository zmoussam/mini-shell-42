/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-hous <mel-hous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 13:14:02 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/13 16:22:12 by mel-hous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../lexer/lexer.h"
# include "../libft/libft.h"
# include <readline/readline.h>
# include "../utils/utils.h"

# define MISSMATCH (void *)-1

typedef struct s_rdr_node
{
	t_token_type			type;
	char					*file;
	struct s_rdr_node		*next;
}			t_rdr_node;
typedef struct s_parser_node
{
	t_token_type			type;
	char					**av;
	int						ac;
	t_rdr_node				*rdrlst;
	struct s_parser_node	*left;
	struct s_parser_node	*right;
}			t_parser_node;

t_parser_node	*check_pipe(t_lexer *lexer);
t_parser_node	*ft_pipe_line(t_lexer *lexer);
t_parser_node	*collect_cmd(t_lexer *lexer);
t_parser_node	*parse(char *input);
t_parser_node	*parse_input(t_lexer *lexer);
t_cmd			*cmd_ccomponents(t_lexer *lexer, t_rdr_node	**rdr);
t_parser_node	*node_create(t_cmd **av, t_rdr_node *rdrlist, t_token_type tp);
char			**av_creat(t_cmd **list);
t_rdr_node		*collect_rdr(t_lexer	*lexer, t_rdr_node	*rdr,
					t_token	token);
void			rdr_addback(t_rdr_node **lst, t_rdr_node *_new);
void			node_del(t_parser_node **node);
void			node_ptr(t_parser_node **node, t_parser_node *left,
					t_parser_node *right);
void			rdr_clear(t_rdr_node **lst);
void			print_error(t_token token);
void			handler(int signum);

#endif
