/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zmoussam <zmoussam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 14:38:48 by mel-hous          #+#    #+#             */
/*   Updated: 2022/11/13 18:42:35 by zmoussam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"

static char	**ft_clear_split(char **tab)
{
	unsigned int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static int	nb_words(const char *str, char c)
{
	int	i;
	int	words;

	words = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i + 1] == c || str[i + 1] == '\0') == 1
			&& (str[i] == c || str[i] == '\0') == 0)
			words++;
		i++;
	}
	return (words);
}

static void	write_word(char *dest, const char *s, char c)
{
	int	i;

	i = 0;
	while ((s[i] == c || s[i] == '\0') == 0)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
}

static char	**cpy_split(char **dest, const char *str, char c)
{
	int		i;
	int		j;
	int		word;

	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i++;
		else
		{
			j = 0;
			while ((str[i + j] == c || str[i + j] == '\0') == 0)
				j++;
			dest[word] = (char *)malloc(sizeof(char) * (j + 1));
			if (dest[word] == NULL)
				return (ft_clear_split(dest));
			write_word(dest[word], str + i, c);
			i += j;
			word++;
		}
	}
	return (dest);
}

char	**ft_split(const char *str, char c)
{
	char	**dest;
	int		words;

	if (!str)
		return (NULL);
	words = nb_words(str, c);
	dest = (char **)malloc(sizeof(char *) * (words + 1));
	if (dest == NULL)
		return (NULL);
	dest[words] = 0;
	if (cpy_split(dest, str, c) == NULL)
		return (NULL);
	return (dest);
}
