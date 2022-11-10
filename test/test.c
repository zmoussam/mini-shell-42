
#include<stdio.h>
#include<stdlib.h>


char	*ft_strdup(const char *s1)
{
	char	*copy;
	int		size;
	int		j;

	size = 0;
	while (s1[size])
		size++;
	copy = (char *)malloc((size + 1) * sizeof(char));
	if (copy == NULL)
		return (copy);
	j = 0;
	while (s1[j])
	{
		copy[j] = s1[j];
		j++;
	}
	copy[j] = '\0';
	return (copy);
}
size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0 ;
	while (str[i])
		i++;
	return (i);
}
char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!c)
		return ((char *)s + ft_strlen(s));
	while (s[i])
	{
		if (s[i] == (unsigned char)c)
			return ((char *)s + i);
		i++;
	}
	return (0);
}
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int	j;
	unsigned int	len;

	len = ft_strlen(src);
	j = 0;
	if (dstsize != 0)
	{
		while (src[j] && j < (dstsize - 1))
		{
			dst[j] = src[j];
			j++;
		}
		dst[j] = '\0';
	}
	return (len);
}
static int	chr_first_index(const char *s1, const char *set)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	i = 0;
	while (i < len)
	{
		if (ft_strchr(set, s1[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

static int	chr_last_index(const char *s1, const char *set)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	i = 0;
	while (i < len)
	{
		if (ft_strchr(set, s1[len - i - 1]) == 0)
			break ;
		i++;
	}
	return (len - i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;
	int		new_size;

	if (!s1 || !set)
		return (NULL);
	start = chr_first_index(s1, set);
	end = chr_last_index(s1, set);
	new_size = end - start;
	if (set == NULL)
		return (ft_strdup((char *)s1));
	if (start >= end)
		return (ft_strdup(""));
	str = (char *)malloc(sizeof(char) * (new_size + 1));
	if (str == NULL)
		return (NULL);
	ft_strlcpy(str, s1 + start, new_size + 1);
	return (str);
}

int main()
{
    printf("name = %s\n", ft_strtrim("t+++", "+"));
}