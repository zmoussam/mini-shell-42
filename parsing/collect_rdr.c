/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_rdr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 16:36:04 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/14 01:42:23 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"
#include <fcntl.h>
#include <string.h>
#include <errno.h>

static int	get_heredoc_l(char *f, int fd, char *line, bool expand)
{
	t_token	expanded;
	t_lexer	*lexer;

	if (expand)
	{
		lexer = lex_init(line);
		expanded = lex_var(*lexer, ft_strlen(lexer->full_str));
		if (!expanded.pos)
		{
			close(fd);
			unlink(f);
			free(f);
			free(line);
			return (-1);
		}
		put_line(expanded.pos, fd);
		free(lexer);
		free(expanded.pos);
	}
	else
		put_line(line, fd);
	return (0);
}

static int	heredoc_handler(char *f, char *delim, bool expand)
{
	int		fd;
	char	*line;

	fd = open(f, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("minishel: ", 2);
		ft_putstr_fd(f, 2);
		ft_putstr_fd(": ", 2);
		printf("minishell: %s:\n", strerror(errno));
		return (-1);
	}
	line = readline(">");
	while (line)
	{
		if (g_lbv.check_signal == 1 || !ft_strcmp(line, delim))
			break ;
		if (get_heredoc_l(f, fd, line, expand))
			return (-1);
		free(line);
		line = readline(">");
	}
	free(line);
	close(fd);
	return (0);
}

static char	*heredoc_filename(t_token t, char *delim)
{
	char		*file;
	static int	i = 0;
	bool		exp;
	char		*n_file;

	exp = !ft_memchr(t.pos, DEF_SINGEL_Q, t.len);
	exp = (exp && !ft_memchr(t.pos, DEF_DOUBEL_Q, t.len));
	n_file = ft_itoa(i);
	if (delim)
		remove_q(delim);
	if (n_file)
		file = ft_strjoin("/tmp/minishell-heredoc-", n_file);
	free(n_file);
	if (!delim || !n_file || !file || heredoc_handler(file, delim, exp))
	{
		printf("minishell: %s:\n", strerror(errno));
		free(delim);
		free(file);
		return (NULL);
	}
	free(delim);
	i++;
	return (file);
}

static char	*rdr_filename(t_token file)
{
	char	*s;

	if (file.type == WLDC)
	{
		if (wc_size(file.wildcard) != 1)
		{
			ft_putstr_fd("minishell ", 2);
			ft_putnstr(file.pos, file.len, 2);
			ft_putstr_fd(": ambiguous redirect", 2);
			wc_clear(&file.wildcard);
			return (NULL);
		}
		s = file.wildcard->d_name;
	}
	else if (file.type == VAR)
		s = ft_substr(file.pos, 0, ft_strlen(file.pos));
	else
		s = ft_substr(file.pos, 0, file.len);
	return (s);
}

t_rdr_node	*collect_rdr(t_lexer	*lexer, t_rdr_node	*rdr, t_token token)
{
	token = get_next_token(lexer);
	if (token.type != WORD && token.type != WLDC && token.type != VAR)
	{
		ft_putstr_fd("minishell :syntax error near unexpected token ", 2);
		write(2, "'", 1);
		ft_putnstr(token.pos, token.len, 2);
		write(2, "'\n", 2);
		return (MISSMATCH);
	}
	rdr = malloc(sizeof(t_rdr_node));
	if (!rdr)
	{
		perror("minishell");
		return (NULL);
	}
	rdr->next = NULL;
	rdr->type = lexer->prev_type.type;
	if (rdr->type == HERDOC)
		rdr->file = heredoc_filename(token, ft_substr(token.pos, 0, token.len));
	else
		rdr->file = rdr_filename(token);
	if (rdr->file)
		return (rdr);
	free(rdr);
	return (NULL);
}
