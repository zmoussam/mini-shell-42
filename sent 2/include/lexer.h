/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 15:27:42 by syakoubi          #+#    #+#             */
/*   Updated: 2022/05/30 16:19:49 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# define LEXER_METACHARS	" \t\n|&()<>"

# include <stddef.h>
# include <stdbool.h>

typedef enum e_lexer_errno
{
	LEXER_ETOK,
	LEXER_EEOF,
}	t_lexer_errno;

typedef enum e_token_type
{
	ERROR = -1,
	EOF_TOKEN,
	STRING,
	OP_RDR_IN,
	OP_RDR_HEREDOC,
	OP_RDR_OUT,
	OP_RDR_OUT_APP,
	OP_PIPE,
	OP_AND,
	OP_OR,
	LPAREN,
	RPAREN,
}	t_token_type;

typedef struct s_lexer
{
	const char		*full_input;
	const char		*input;
	size_t			pos;
	t_lexer_errno	errno;
}	t_lexer;

typedef struct s_token
{
	const char		*s;
	size_t			len;
	t_token_type	type;
}	t_token;

t_lexer	lexer_init(const char *input);
t_token	lexer_peek(t_lexer *lexer);
t_token	lexer_next(t_lexer *lexer);
void	lexer_perror(t_lexer lexer);

#endif /* LEXER_H */
