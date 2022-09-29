/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_glob.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakoubi <splentercell.1997@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 14:25:23 by syakoubi          #+#    #+#             */
/*   Updated: 2022/06/25 18:38:13 by syakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "shell.h"
#include "utils.h"
#include "libft.h"
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

static t_list	*insert(t_list **lst, char *d_name)
{
	char	*dup;
	t_list	*new;

	dup = ft_strdup(d_name);
	new = ft_lstnew(dup);
	if (!dup || !new)
	{
		ft_lstclear(lst, free);
		free(dup);
		free(new);
		return (NULL);
	}
	ft_lstinsert_sorted(lst, new, (t_lft_cmpfn)ft_strcmp);
	return (new);
}

t_list	*get_matches(char *g)
{
	DIR				*dirp;
	struct dirent	*ent;
	t_list			*lst;

	lst = NULL;
	dirp = opendir(".");
	if (!dirp)
		return (NULL);
	ent = readdir(dirp);
	while (ent)
	{
		if (glob_match_enc(g, ent->d_name) && !insert(&lst, ent->d_name))
			break ;
		ent = readdir(dirp);
	}
	closedir(dirp);
	return (lst);
}

t_list	*expand_glob(t_token token)
{
	char	*s;
	t_list	*lst;

	s = ft_substr(token.s, 0, token.len);
	if (!s)
	{
		perror(SH_NAME);
		return (NULL);
	}
	lst = NULL;
	errno = 0;
	if (is_glob_enc(s))
		lst = get_matches(s);
	if (!lst && (errno != 0 || !insert(&lst, remove_quotes_enc(s))))
		perror(SH_NAME);
	free(s);
	return (lst);
}
