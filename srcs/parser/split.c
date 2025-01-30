#include "cube.h"

int	countwords(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i] != '\0')
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		if (s[i] == c)
			i++;
	}
	return (count);
}

int	wordlen(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	int		wordcount;
	char	**ret;
	int		i;

	if (!s)
		return (0);
	wordcount = countwords(s, c);
	ret = malloc(sizeof(char *) * (wordcount + 1));
	if (!ret)
		return (0);
	i = 0;
	while (wordcount--)
	{
		while (*s == c && *s)
			s++;
		ret[i] = ft_substr((char *)s, 0, wordlen((char *)s, c));
		if (!ret[i])
			return (0);
		s += wordlen((char *)s, c);
		i++;
	}
	ret[i] = NULL;
	return (ret);
}