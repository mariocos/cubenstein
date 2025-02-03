#include "../cube.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = s;
	while (i < n)
	{
		*ptr = c;
		i++;
		ptr++;
	}
	return (s);
}

int	is_map_char(char c)
{
	if (c == '1' || c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == '0' || c == '9')
		return (1);
	return (0);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (src[count] != '\0')
		count++;
	if (size != 0)
	{
		while (i + 1 < size && src[i] != '\0')
		{
			if (is_map_char(src[i]))
				dst[i] = src[i];
			i++;
		}
	}
	return (count);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	if (s1 == NULL || s2 == NULL)
		return (0);
	while (*s1 && *s2 && (*s1 == *s2))
	{
		if (!*s1 || !*s2)
			break ;
		s1++;
		s2++;
	}
	return (*(const unsigned char *)s1 - *(const unsigned char *)s2);
}


char	*ft_substr(char *s, int start, int len)
{
	char	*ret;

	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	if ((start + len) > ft_strlen(s))
		len = ft_strlen(s) - start;
	ret = malloc(len + 1);
	if (ret == NULL)
		return (NULL);
	ft_strlcpy(ret, s + start, len + 1);
	return (ret);
}

char	*ft_strdup(char *s)
{
	int		str_len;
	char	*dest;
	int		i;

	i = 0;
	str_len = ft_strlen(s) + 1;
	dest = malloc(str_len + 1);
	while (s && s[i] != '\0')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}


void	put_str_check(char *str)
{
	int	i;

	i = 0;
	if (!str)
	{
		printf("you called putstr with a null str\n");
		return ;
	}
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	if (str[i] == '\0')
		printf("its null terminated with size %d\n", i);
}