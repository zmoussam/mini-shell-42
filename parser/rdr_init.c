/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/31 00:26:34 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/25 20:07:18 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_internal.h"
#include "lexer.h"
#include "libft.h"
#include "shell.h"
#include "utils.h"
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <readline/readline.h>

static int	write_heredoc_line(char *f, int fd, char *line, bool expand)
{
	char	*expanded;

	expanded = NULL;
	if (expand)
	{
		expanded = expand_params(line);
		if (!expanded)
		{
			close(fd);
			unlink(f);
			free(f);
			free(line);
			return (-1);
		}
		ft_putstr_fd(expanded, fd);
		ft_putchar_fd('\n', fd);
		free(expanded);
	}
	else
	{
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
	}
	return (0);
}

static int	read_heredoc(char *f, char *delim, bool expand)
{
	int		fd;
	char	*line;

	fd = open(f, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		ft_putstr_fd(SH_NAME ": ", 2);
		ft_putstr_fd(f, 2);
		ft_putstr_fd(": ", 2);
		perror(NULL);
		return (-1);
	}
	line = readline(SH_PS2);
	while (line)
	{
		if (!strcmp(line, delim))
			break ;
		if (write_heredoc_line(f, fd, line, expand))
			return (-1);
		free(line);
		line = readline(SH_PS2);
	}
	free(line);
	close(fd);
	return (0);
}

static char	*get_heredoc_filename(t_token t)
{
	static int	n = 0;
	char		*n_str;
	char		*delim;
	char		*f;
	bool		expand;

	expand = !ft_memchr(t.s, ENCODED_SINGLEQ, t.len);
	expand = (expand && !ft_memchr(t.s, ENCODED_DOUBLEQ, t.len));
	n_str = ft_itoa(n);
	delim = ft_substr(t.s, 0, t.len);
	if (delim)
		remove_quotes_enc(delim);
	if (n_str)
		f = ft_strjoin("/tmp/" SH_NAME "-heredoc-", n_str);
	free(n_str);
	if (!delim || !n_str || !f || read_heredoc(f, delim, expand))
	{
		perror(SH_NAME);
		free(delim);
		free(f);
		return (NULL);
	}
	free(delim);
	n++;
	return (f);
}

static char	*get_filename(t_token token)
{
	t_list	*exp;
	char	*s;

	exp = expand_glob(token);
	if (!exp)
		return (NULL);
	if (ft_lstsize(exp) != 1)
	{
		ft_putstr_fd(SH_NAME " ", 2);
		ft_putnstr_fd(token.s, token.len, 2);
		ft_putstr_fd(": ambiguous redirect", 2);
		ft_lstclear(&exp, free);
		return (NULL);
	}
	s = exp->content;
	ft_lstdelone(exp, NULL);
	return (s);
}

t_rdr	*rdr_init(t_rdr_type type, t_token str)
{
	t_rdr	*rdr;

	rdr = malloc(sizeof(t_rdr));
	if (!rdr)
	{
		perror(SH_NAME);
		return (NULL);
	}
	rdr->type = type;
	if (rdr->type == RDR_HEREDOC)
		rdr->f = get_heredoc_filename(str);
	else
		rdr->f = get_filename(str);
	if (rdr->f)
		return (rdr);
	free(rdr);
	return (NULL);
}
